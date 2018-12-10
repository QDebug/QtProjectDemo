#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "thread.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    threadTest();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::threadTest()
{
    m_thread = new Thread();
}

void MainWindow::on_startButton_clicked()
{
    m_thread->threadStart();
    qDebug() << "start clicked!";
}

void MainWindow::on_pauseButton_clicked()
{
    m_thread->threadPause();
    qDebug() << "pause clicked!";
}

void MainWindow::on_resumeButton_clicked()
{
    m_thread->threadResume();
    qDebug() << "resume clicked!";
}

void MainWindow::on_stopButton_clicked()
{
    m_thread->threadStop();
    qDebug() << "stop clicked!";
}
