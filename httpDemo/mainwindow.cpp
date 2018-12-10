#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QSettings>
#include <QPainter>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_downloadManager(NULL)
  , m_httpClient(NULL)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    loadStysheet();

    colorTest();

    m_httpClient = new HttpClient();
    connect(m_httpClient, SIGNAL(signalDownLoadProcess(qint64,qint64)), this, SLOT(slotProgressBar(qint64,qint64)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testHttpClient()
{
    QNetworkRequest req;



    //腾讯QQ下载
    {
        //https://qd.myapp.com/myapp/qqteam/tim/down/tim_pc.exe
        //https://netix.dl.sourceforge.net/project/qtav/release/1.11.0/QtAV1.11.0-MinGW32.exe
        req.setUrl(QUrl("https://qd.myapp.com/myapp/qqteam/tim/down/tim_pc.exe"));

        m_httpClient->get(req);
        QByteArray recvData = m_httpClient->data();

        if (!HttpClient::writeFile("QQ.exe", recvData))
            return;
    }




    /*
    //巧虎网获取信息
    {
        req.setUrl(QUrl("https://www.qiaohu.com/jsonDate/switchData.json?ran=0.9337392607168618"));
        req.setRawHeader("Referer", "https://www.qiaohu.com/Login/GoLogin");
        req.setRawHeader("X-Requested-With", "XMLHttpRequest");

        m_httpClient->get(req);
        QByteArray recvData = m_httpClient->data();

        if (!HttpClient::writeFile("qiaohuwang.txt", recvData))
            return;
    }
    */


    /*
    //巧虎网post信息
    {
        req.setUrl(QUrl("http://i.ytsg.com/api/reader/getReaderPhoto"));
        //req.setRawHeader("Upgrade-Insecure-Requests", "1");
        //req.setRawHeader("Referer", "https://www.qiaohu.com/Login/GoLogin");
        //req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        QVariantMap postMap;
        postMap.insert("username", "03");
        postMap.insert("password", "03");
        postMap.insert("telephone", "");
        postMap.insert("verifyCode", "");
        postMap.insert("loginType", "");
        postMap.insert("subactivecode", "");
       // QByteArray postData = HttpClient::buildQuery(postMap);
        QByteArray postData = "142326198412061213";
        if (!m_httpClient->post(req, postData))
            return;

        QByteArray recvData = m_httpClient->data();

        if (!HttpClient::writeFile("login.txt", recvData))
            return;
    }
    */


    /*
    //验证buildQuery正确性
    {
        QVariantMap postMap;
        postMap.insert("username", "03");
        postMap.insert("password", "03");
        postMap.insert("telephone", "110");
        postMap.insert("verifyCode", "12580");
        postMap.insert("loginType", "y");
        postMap.insert("subactivecode", "qw");
        QByteArray postData = HttpClient::buildQuery(postMap);
    }
    */

    /*
    //测试JSON解析
    {
        //遍历以下格式的json字符串内容
        //{"data":[{"name":"7~12月龄","url":"baobao1"},{"name2":"7~12月龄","url2":"baobao1"}]}
        QFile file("qiaohuwang.txt");
        if (!file.open(QIODevice::ReadOnly))
            return;

        QByteArray fileData = file.readAll();
        QString fileStr = QString::fromUtf8(fileData);

        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileStr.toUtf8(), &jsonError);

        if(jsonError.error == QJsonParseError::NoError)
        {
            QVariantMap tempMap = jsonDoc.toVariant().toMap();
            QVariantList dataList = tempMap.value("data").toList();
            foreach (QVariant data, dataList)
            {
                QVariantMap detailMap = data.toMap();
                qDebug() << "name: " << detailMap.value("name").toString();
                qDebug() << "url: " << detailMap.value("url").toString();
                qDebug() << "text: " << detailMap.value("text").toString();
            }
        }


        //重新组装成以下格式
        //{"data":[{"name":"7~12月龄","url":"baobao1"},{"name2":"7~12月龄","url2":"baobao1"}]}
        QVariantMap tempMap;
        tempMap.insert("name", "7~12月龄");
        tempMap.insert("url", "baobao1");

        QVariantMap tempMap2;
        tempMap2.insert("name2", "7~12月龄");
        tempMap2.insert("url2", "baobao1");

        QVariantList dataList;
        dataList.append(tempMap);
        dataList.append(tempMap2);

        QVariantMap dataMap;
        dataMap.insert("data", dataList);
        QJsonDocument jsonDocument = QJsonDocument::fromVariant(dataMap);
        qDebug() << jsonDocument.toJson(QJsonDocument::Compact);
    }
    */

    //测试QSettings
    {
        //保存配置文件
        QSettings saveSettings("saveSettings.ini", QSettings::IniFormat);
        saveSettings.setValue("mainwindow/size", "123");
        saveSettings.setValue("mainwindow/long", "123654");
        saveSettings.setValue("mainwindow/kuan", "0089");
        saveSettings.setValue("family/father", "8y28");
        saveSettings.setValue("family/mother", "17821");

        saveSettings.beginGroup("school");
        saveSettings.setValue("teacher", "mr.wang");
        saveSettings.setValue("teacher", "mr.zhang");
        saveSettings.endGroup();

        saveSettings.beginGroup("class");
        saveSettings.setValue("student", "stu.li");
        saveSettings.setValue("student", "stu.xiao");
        saveSettings.endGroup();
    }
    return;
}

void MainWindow::slotProgressBar(qint64 bytesSent, qint64 bytesTotal)
{
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(bytesSent);
}

void MainWindow::on_pushButton_clicked()
{
    testHttpClient();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //:/image/image/desktop.jpeg
//    QPixmap pixmap = QPixmap(":/image/image/test2.jpg").scaled(this->size());
//    QPainter painter(this);
//    painter.drawPixmap(this->rect(), pixmap);
}

void MainWindow::loadStysheet()
{
    //:/image/image/my_coffice.qss
    QFile file(":/theme/Theme/coffee.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);

    ui->progressBar->setValue(49);
}

void MainWindow::on_comboBox_currentIndexChanged()
{
    QString fileName = ui->comboBox->currentText();
    //QString fileName = "coffee";
    QFile file(QString(":/theme/Theme/%1.qss").arg(fileName));
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::colorTest()
{
    QString color = QString("<font color=\"red\">this is plaintextedit test @red</font>");
    ui->plainTextEdit->appendHtml(color);

    color = QString("<font color='#1020ff'>this is plaintextedit test @#1020ff</font>");
    ui->plainTextEdit->appendHtml(color);

    color = QString("<font color='green'>this is plaintextedit test @green</font>");
    ui->plainTextEdit->appendHtml(color);
}

void MainWindow::on_downLoadButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "",
                               tr("Exes (*.exe)"));

    // 从界面获取下载链接;
    m_url = ui->downLoadLineEdit->text();
    if (m_downloadManager == NULL)
    {
        m_downloadManager = new DownLoadManager(this);
        connect(m_downloadManager , SIGNAL(signalDownloadProgress(qint64, qint64)), this, SLOT(onDownloadProcess(qint64, qint64)));
        connect(m_downloadManager, SIGNAL(signalReplyFinished(int)), this, SLOT(onReplyFinished(int)));
    }

    // 这里先获取到m_downloadManager中的url与当前的m_url 对比，如果url变了需要重置参数,防止文件下载不全;
    QString url = m_downloadManager->getDownloadUrl();
    if (url != m_url)
    {
        m_downloadManager->reset();
    }
    m_downloadManager->setDownInfo(true);
    m_downloadManager->downloadFile(m_url, fileName);
    m_timeRecord.start();
    m_timeInterval = 0;
    ui->downStateLabel->setText(QStringLiteral("正在下载"));
}

void MainWindow::on_stopDownButton_clicked()
{
    ui->downStateLabel->setText(QStringLiteral("停止下载"));
     if (m_downloadManager != NULL)
     {
         m_downloadManager->stopDownload();
     }
    ui->downSpeedLabel->setText("0 KB/S");
    ui->remainTimeLabel->setText("0s");
}

void MainWindow::on_closeDownButton_clicked()
{
    m_downloadManager->closeDownload();
    ui->downProgressBar->setValue(0);
    ui->downSpeedLabel->setText("0 KB/S");
    ui->remainTimeLabel->setText("0s");
    ui->downStateLabel->setText(QStringLiteral("关闭下载"));
    ui->currentSizeLabel->setText("0 B");
    ui->fileSizeLabel->setText("0 B");
}

// 更新下载进度;
void MainWindow::onDownloadProcess(qint64 bytesReceived, qint64 bytesTotal)
{
    // 输出当前下载进度;
    // 用到除法需要注意除0错误;
    qDebug() << QString("%1").arg(bytesReceived * 100 / bytesTotal + 1);
    // 更新进度条;
    ui->downProgressBar->setMaximum(bytesTotal);
    ui->downProgressBar->setValue(bytesReceived);

    // m_intervalDownload 为下次计算速度之前的下载字节数;
    m_intervalDownload += bytesReceived - m_currentDownload;
    m_currentDownload = bytesReceived;

    uint timeNow = m_timeRecord.elapsed();

    // 超过0.3s更新计算一次速度;
    if (timeNow - m_timeInterval > TIME_INTERVAL)
    {
        qint64 ispeed = m_intervalDownload * 1000 / (timeNow - m_timeInterval);
        QString strSpeed = DownLoadManager::transformUnit(ispeed, true);
        ui->downSpeedLabel->setText(strSpeed);
        // 剩余时间;
        qint64 timeRemain = (bytesTotal - bytesReceived) / ispeed;
        ui->remainTimeLabel->setText(DownLoadManager::transformTime(timeRemain));

        ui->currentSizeLabel->setText(DownLoadManager::transformUnit(m_currentDownload));
        ui->fileSizeLabel->setText(DownLoadManager::transformUnit(bytesTotal));

        m_intervalDownload = 0;
        m_timeInterval = timeNow;
    }
}

// 下载完成;
void MainWindow::onReplyFinished(int statusCode)
{
    // 根据状态码判断当前下载是否出错;
    if (statusCode >= 200 && statusCode < 400)
    {
        qDebug() << "Download Failed";
    }
    else
    {
        qDebug() << "Download Success";
        ui->downStateLabel->setText("下载完成");
    }
}

void MainWindow::initDownLoadManager()
{
//    m_timeInterval = new QTimer();
//    m_timeRecord = new QTimer();
}

void MainWindow::on_updateButton_clicked()
{
    m_update = new Update;
    m_update->readVersionFromServer();
}
