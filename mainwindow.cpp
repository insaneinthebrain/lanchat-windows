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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wkthread = new workThread(this);
    connect(wkthread, SIGNAL(MsgChanged(QString)), this, SLOT(onMsgChanged(QString)));
    connect(wkthread, SIGNAL(Socks(int,int)), this, SLOT(onSocks(int,int)));
    connect(wkthread, SIGNAL(Credentials(QString,QString,QString)), this, SLOT(onCredentials(QString,QString,QString)));
    connect(wkthread, SIGNAL(ReportError(QString)), this, SLOT(onError(QString)));
    connect(this, SIGNAL(Conn_Type(QString,QString)), wkthread, SLOT(onConn_Type(QString,QString)));

}

MainWindow::~MainWindow()
{

    delete ui;
}



void MainWindow::on_btnSend_clicked()
{
    for(int x=0; x<80; x++){
                send_msg[x]= *"";
            }

    QString new_msg = ui->textEdit->toPlainText();

    for(int x=0; x<80; x++){
        send_msg[x] = new_msg.toUtf8().constData()[x];
    }

    if(ConnType=="Listen"){
        send(conn_in_sock, send_msg, sizeof(send_msg), 0);
    }
    if(ConnType=="Connect"){
        send(out_sock, send_msg, sizeof(send_msg), 0);
    }
    ui->textEdit->setText("");

    ui->textEdit_2->setTextColor(Qt::darkBlue);
    ui->textEdit_2->append(yourName + ": ");
    ui->textEdit_2->setTextColor(Qt::black);
    ui->textEdit_2->insertPlainText(new_msg);

}

void MainWindow::on_btnListen_clicked()
{
    connect_to_ip="";
    ConnType="Listen";
    emit Conn_Type(ConnType, connect_to_ip);
    wkthread->start();

}

void MainWindow::on_btnConnect_clicked()
{
    if(ui->lineEdit->text() != ""){
        connect_to_ip=ui->lineEdit->text();
        ConnType="Connect";
        emit Conn_Type(ConnType, connect_to_ip);
        wkthread->start();
    }
}


void MainWindow::onCredentials(QString wIP, QString theyName, QString yoName){
    IPAddy=wIP;
    theirName=theyName;
    yourName=yoName;

    if(ConnType=="Listen"){
        ui->textEdit_2->setTextColor(Qt::darkGray);
        ui->textEdit_2->append(theirName + " connected from " + IPAddy);
        ui->textEdit_2->setTextColor(Qt::darkMagenta);
        ui->textEdit_2->append("Now chatting with " + theirName + "\n");
    }

    if(ConnType=="Connect"){
        ui->textEdit_2->setTextColor(Qt::darkGray);
        ui->textEdit_2->append("Connected to " + connect_to_ip + " as " + yourName);
        ui->textEdit_2->setTextColor(Qt::darkMagenta);
        ui->textEdit_2->append("Now chatting with " + theirName + "\n");

    }

}

void MainWindow::onMsgChanged(QString newMsg){

    ui->textEdit_2->setTextColor(Qt::darkRed);
    ui->textEdit_2->append(theirName + ": " );
    ui->textEdit_2->setTextColor(Qt::black);
    ui->textEdit_2->insertPlainText(newMsg);

}

void MainWindow::onSocks(int sock1, int sock2){
    conn_in_sock=sock1;
    out_sock=sock2;
}

void MainWindow::onError(QString errmsg){

    ui->textEdit_2->setTextColor(Qt::red);
    ui->textEdit_2->append(errmsg);
}

