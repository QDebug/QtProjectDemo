#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "httpclient.h"
#include <QNetworkProxy>
#include "downloadmanager.h"
#include <QTimer>
#include "update/update.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void testHttpClient();
    void paintEvent(QPaintEvent *e);

    void loadStysheet();

    void colorTest();

    //初始化下载
    void initDownLoadManager();


public slots:
    void slotProgressBar(qint64 bytesSent, qint64 bytesTotal);
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged();

    void on_downLoadButton_clicked();
    void on_stopDownButton_clicked();
    void on_closeDownButton_clicked();
    void onDownloadProcess(qint64 bytesReceived, qint64 bytesTotal);
    void onReplyFinished(int statusCode);

    void on_updateButton_clicked();
private:
    Ui::MainWindow *ui;
    HttpClient *m_httpClient;
    Update *m_update;

    QString m_url;
    DownLoadManager *m_downloadManager;
    QTime m_timeRecord;
    uint m_timeInterval;
    qint64 m_intervalDownload;
    qint64 m_currentDownload;
};

#endif // MAINWINDOW_H
