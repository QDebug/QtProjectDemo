#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include "httpclient.h"

#define UNIT_KB 1024            //KB
#define UNIT_MB 1024*1024       //MB
#define UNIT_GB 1024*1024*1024  //GB
#define TIME_INTERVAL 300       //0.3s

class DownLoadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownLoadManager(QObject *parent = NULL);
    ~DownLoadManager();

    void setDownInfo(bool isSupportBreakPoint);
    QString getDownloadUrl();
    void downloadFile(QString url , QString fileName);
    void stopWork();
    void stopDownload();
    void reset();
    void removeFile(QString fileName);
    void closeDownload();


    static QString transformUnit(qint64 bytes , bool isSpeed = false);
    static QString transformTime(qint64 seconds);

signals:
    void signalDownloadProgress(qint64 current, qint64 total);
    void signalReplyFinished(int code);
    void signalDownloadError();

public slots:
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onReadyRead();
    void onFinished();
    void onError(QNetworkReply::NetworkError code);

private:
    //QNetworkAccessManager *m_networkManager;
    HttpClient *m_httpClient;
    QUrl m_url;
    QString m_fileName;
    bool m_isSupportBreakPoint;
    qint64 m_bytesReceived;
    qint64 m_bytesTotal;
    qint64 m_bytesCurrentReceived;
    bool m_isStop;
    QNetworkReply *m_reply;
};

#endif // DOWNLOADMANAGER_H
