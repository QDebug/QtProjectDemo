#include "update.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QUrl>
#include <QNetworkRequest>
#include <QSettings>

Update::Update(QObject *parent) : QObject(parent)
  , m_httpclient(new HttpClient(this))
{

}

bool Update::checkMD5(QByteArray data,const QString fileName)
{
    QString md5HashValue = QCryptographicHash::hash(data, QCryptographicHash::Md5).toHex();

#ifdef _DEBUG
    qDebug() << "md5HashValue" << md5HashValue;
    qDebug() << "MD5Hash" << MD5Hash.value(fileName);
#endif

    if (md5HashValue == MD5Hash.value(fileName))
        return true;
    else
        return false;
}

void Update::reboot()
{
    system("shutdown -r -t 0");
}

bool Update::readVersionFromServer()
{
    QString url("https://blog.csdn.net/wangyeqiang/article/details/8144680");
    QNetworkRequest req(url);
    QVariantMap postMap;
    postMap.insert("version", "1.0");
    QByteArray postData = HttpClient::buildQuery(postMap);
    if (!m_httpclient->post(req, postData))
    //if (!m_httpclient->get(req))
    {
        outputMessage(m_httpclient->errorDesc());
        return false;
    }
    QString m_text = m_httpclient->text();

    return true;
}

bool Update::readVersionFromLocal()
{
    QSettings localVerSettings("setting.ini", QSettings::IniFormat);
    localVerSettings.beginGroup("Versions");

    localVerSettings.endGroup();


    return true;
}

void Update::outputMessage(const QString &msg)
{
    emit signalMessage(msg);

    qDebug() << msg;
}
