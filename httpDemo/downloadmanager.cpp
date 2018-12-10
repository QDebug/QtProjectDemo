#include "downloadmanager.h"
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

#define DOWNLOAD_FILE_SUFFIX "_tmp"

DownLoadManager::DownLoadManager(QObject *parent)
    : QObject(parent)
    , m_httpClient(NULL)
    , m_url(QUrl(""))
    , m_fileName("")
    , m_isSupportBreakPoint(false)
    , m_bytesReceived(0)
    , m_bytesTotal(0)
    , m_bytesCurrentReceived(0)
    , m_isStop(true)
{
    m_httpClient = new HttpClient(this);
}

DownLoadManager::~DownLoadManager()
{}

void DownLoadManager::setDownInfo(bool isSupportBreakPoint)
{
    m_isSupportBreakPoint = isSupportBreakPoint;
}

QString DownLoadManager::getDownloadUrl()
{
    return m_url.toString();
}

void DownLoadManager::downloadFile(QString url, QString fileName)
{
    if (m_isStop)
    {
        m_isStop = false;
        m_url = QUrl(url);

        //QString fileName = m_url.fileName();

        m_fileName = fileName + DOWNLOAD_FILE_SUFFIX;

        if (m_bytesCurrentReceived <= 0)
        {
            removeFile(m_fileName);
        }

        QNetworkRequest request;
        request.setUrl(m_url);

        if(m_isSupportBreakPoint)
        {
            QString strRange = QString("bytes=%1-").arg(QString::number(m_bytesCurrentReceived));
            request.setRawHeader("Range", strRange.toLatin1());
        }

        m_reply = m_httpClient->networkAccessManager()->get(request);
        connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
        connect(m_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
        connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    }
}

void DownLoadManager::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (!m_isStop)
    {
        m_bytesReceived = bytesReceived;
        m_bytesTotal = bytesTotal;

        emit signalDownloadProgress(m_bytesReceived + m_bytesCurrentReceived, m_bytesTotal + m_bytesCurrentReceived);
    }
}

void DownLoadManager::onReadyRead()
{
    if (!m_isStop)
    {
        QFile file(m_fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            file.write(m_reply->readAll());
        }
        file.close();
    }
}

void DownLoadManager::onFinished()
{
    m_isStop = true;

    QVariant statusCode = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (m_reply->error() == QNetworkReply::NoError)
    {
        QFileInfo fileInfo(m_fileName);
        if (fileInfo.exists())
        {
            int index = m_fileName.lastIndexOf(DOWNLOAD_FILE_SUFFIX);
            QString realName = m_fileName.left(index);
            QFile::rename(m_fileName, realName);
        }
    }
    else
    {
        QString strError = m_reply->errorString();
        qDebug() << "----------" + strError;
    }

    emit signalReplyFinished(statusCode.toInt());
}

void DownLoadManager::stopWork()
{
    m_isStop = true;
    if (m_reply != NULL)
    {
        disconnect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
        disconnect(m_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        disconnect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
        disconnect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
        m_reply->abort();
        m_reply->deleteLater();
        m_reply = NULL;
    }
}

void DownLoadManager::stopDownload()
{
    if (!m_isStop)
    {
        m_bytesCurrentReceived += m_bytesReceived;
        stopWork();
    }
}

void DownLoadManager::reset()
{
    m_bytesCurrentReceived = 0;
    m_bytesReceived = 0;
    m_bytesTotal = 0;
}

void DownLoadManager::removeFile(QString fileName)
{
    QFileInfo fileInfo(fileName);
    if (fileInfo.exists())
    {
        QFile::remove(fileName);
    }
}

void DownLoadManager::closeDownload()
{
    stopWork();
    reset();
    removeFile(m_fileName);
}

void DownLoadManager::onError(QNetworkReply::NetworkError code)
{
    QString strError = m_reply->errorString();
    qDebug() << "__________" + strError;

    closeDownload();
    emit signalDownloadError();
}

// 转换单位;
QString DownLoadManager::transformUnit(qint64 bytes , bool isSpeed)
{
    QString strUnit = " B";
    if (bytes <= 0)
    {
        bytes = 0;
    }
    else if (bytes < UNIT_KB)
    {
    }
    else if (bytes < UNIT_MB)
    {
        bytes /= UNIT_KB;
        strUnit = " KB";
    }
    else if (bytes < UNIT_GB)
    {
        bytes /= UNIT_MB;
        strUnit = " MB";
    }
    else if (bytes > UNIT_GB)
    {
        bytes /= UNIT_GB;
        strUnit = " GB";
    }

    if (isSpeed)
    {
        strUnit += "/S";
    }
    return QString("%1%2").arg(bytes).arg(strUnit);
}

// 转换时间;
QString DownLoadManager::transformTime(qint64 seconds)
{
    QString strValue;
    QString strSpacing(" ");
    if (seconds <= 0)
    {
        strValue = QString("%1s").arg(0);
    }
    else if (seconds < 60)
    {
        strValue = QString("%1s").arg(seconds);
    }
    else if (seconds < 60 * 60)
    {
        int nMinute = seconds / 60;
        int nSecond = seconds - nMinute * 60;

        strValue = QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }
    else if (seconds < 60 * 60 * 24)
    {
        int nHour = seconds / (60 * 60);
        int nMinute = (seconds - nHour * 60 * 60) / 60;
        int nSecond = seconds - nHour * 60 * 60 - nMinute * 60;

        strValue = QString("%1h").arg(nHour);

        if (nMinute > 0)
            strValue += strSpacing + QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }
    else
    {
        int nDay = seconds / (60 * 60 * 24);
        int nHour = (seconds - nDay * 60 * 60 * 24) / (60 * 60);
        int nMinute = (seconds - nDay * 60 * 60 * 24 - nHour * 60 * 60) / 60;
        int nSecond = seconds - nDay * 60 * 60 * 24 - nHour * 60 * 60 - nMinute * 60;

        strValue = QString("%1d").arg(nDay);

        if (nHour > 0)
            strValue += strSpacing + QString("%1h").arg(nHour);

        if (nMinute > 0)
            strValue += strSpacing + QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }

    return strValue;
}
