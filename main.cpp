#include "mainwindow.h"
#include<QMainWindow>
#include <QApplication>
#include <qtextcodec.h>
#include"Scheduler.h"
#include"Slownik.h"


int main(int argc, char *argv[])
{
    QTextCodec::codecForName("UTF-8");
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
