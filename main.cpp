#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //对于是GUI且基于QWidget的Qt应用程序，使用QApplication类
    MainWindow w;
    w.show();//打开图形化界面

    return a.exec();
    //进入主事件循环并等待直到调用exit()
}
