#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "thread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void threadTest();
public slots:

    void on_startButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButton_clicked();
    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;
    Thread *m_thread;
};

#endif // MAINWINDOW_H
