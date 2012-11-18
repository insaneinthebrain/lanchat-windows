#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtCore>
#include <QMainWindow>
#include <QObject>
#include <QtGui>
#include <QThread>
#include "workthread.h"
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <winsock2.h>
#include <Ws2tcpip.h>









int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
