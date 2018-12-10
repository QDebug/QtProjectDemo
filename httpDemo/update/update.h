#ifndef UPDATE_H
#define UPDATE_H

#include <QObject>
#include <QHash>
#include "httpclient.h"

class Update : public QObject
{
    Q_OBJECT
public:
    explicit Update(QObject *parent = nullptr);


    //读取服务器软件版本号
    bool readVersionFromServer();
    //读取本地软件版本号
    bool readVersionFromLocal();
    // 文件MD5值校验
    bool checkMD5(QByteArray data,const QString fileName);
    //重启设备
    void reboot();

    //输出信息
    void outputMessage(const QString &meg);
signals:
    //发送信息
    void signalMessage(const QString &msg);
public slots:

private:
    QHash<QString,QString> MD5Hash;
    HttpClient *m_httpclient;
};

#endif // UPDATE_H
