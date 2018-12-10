#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H


#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>

class QNetworkAccessManager;
class QEventLoop;
class QMutexLocker;
class QMutex;

class HttpClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpClient(QObject *parent = 0);
    ~HttpClient();

    static HttpClient *Instance();

    //设置/获取 QNetworkAccessManager
    QNetworkAccessManager *networkAccessManager() const;
    void setNetworkAccessManager(QNetworkAccessManager *networkAccessManager);

    //以字符串的形式返回网络错误码
    QString errorCode() const;
    //返回网络错误描述
    QString errorDesc() const;
    QString errorString() const;
    void setErrorString(const QString &value);

    bool get(QNetworkRequest request);
    bool post(QNetworkRequest request, const QByteArray &data);
    bool post(QNetworkRequest request, QHttpMultiPart *multiPart);

    //返回reply原始数据
    QByteArray data() const;
    QString text() const;

    //QMap<QByteArray, QByteArray> responseRawHeaders() const;

    //设置公共头
    void insertCommonHeader(const QByteArray &name, const QByteArray &value);
    QMap<QByteArray, QByteArray> commonHeaders() const;
    void setCommonHeaders(const QMap<QByteArray, QByteArray> &commonHeaders);

    //设置/获取 默认字符集
    void setDefaultCharset(const QByteArray &defaultCharset);
    QByteArray getDefaultCharset() const;


    /***************************************************************************/
    //写入文件操作
    static bool writeFile(const QString fileName, const QByteArray &data);
    //组建发送数据
    //username=09&password=09&telephone=&verifyCode=&loginType=username&subactivecode=
    static QByteArray buildQuery(const QVariantMap &postMap, const char *charset = "utf-8");


public slots:
    //下载进度
    void slotDownLoadProcess(qint64 bytesSent, qint64 bytesTotal);
    //处理ssl错误
    void onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
signals:
    //发送下载进度信号
    void signalDownLoadProcess(qint64 bytesSent, qint64 bytesTotal);

private:
    //处理reply返回数据,完成后删除reply
    void processReply(QNetworkReply *reply);

private:
    QEventLoop *m_eventLoop; //事件循环
    QString m_errorString; //返回的错误描述
    QNetworkAccessManager *m_networkAccessManager;
    QByteArray m_data;  //存放网络请求返回的原始数据
    QString m_text; //存放网络请求返回的文本字符串
    int m_httpStatusCode; //HTTP状态码
    QMap<QByteArray, QByteArray> m_commonHeaders; //公共发送头
    QNetworkReply::NetworkError m_error; //网络应答错误返回
    QByteArray m_defaultCharset; //默认字符集解码
    QMap<QByteArray, QByteArray> m_responseRawHeaders; // HTTP响应头

    static QMutex s_fileMutex; //读写文件锁
};

#endif // HTTPCLIENT_H
