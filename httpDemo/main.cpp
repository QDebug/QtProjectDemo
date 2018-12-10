#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // a.setWindowIcon(QIcon("logo.ico"));

    MainWindow w;
    w.show();
    w.setWindowIcon(QIcon(":/logo/Logo/logo.ico"));
    w.setWindowTitle("测试软件");

    return a.exec();
}
