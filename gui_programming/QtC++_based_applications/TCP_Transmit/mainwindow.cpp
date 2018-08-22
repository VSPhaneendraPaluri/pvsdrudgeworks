#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>
#include <QMessageBox>
#include <QString>
#include <QDataStream>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myTCPServer = new QTcpServer(this);
    myTCPSocketForConnect = new QTcpSocket(this);

    listenForNewClients();
    connectToNewHost();

    connect(ui->commandLinkButton, SIGNAL(clicked()), this, SLOT(onTransmitDataToServer()));
}

MainWindow::~MainWindow()
{
    myTCPSocketForListen->disconnectFromHost();
    myTCPSocketForListen->close();

    delete myTCPSocketForListen;
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
        break;

        default:
            break;
    }
}

// ---------------------------------------------------------------------------------------------------------------------------

void MainWindow::listenForNewClients()
{
    if(!myTCPServer->listen(QHostAddress::Any, 4000))
    {
        QMessageBox::information(this, tr("PDU : TCP Server"),
                                 tr("Unable to connect to Server : %1. ").arg(myTCPServer->errorString()));
        close();
        return;
    }
    ui->Label1->setText("Server is listening is for new connections");
    connect(myTCPServer, SIGNAL(newConnection()), this, SLOT(connectToNextPendingClient()));
}

void MainWindow::connectToNextPendingClient()
{
    myTCPSocketForListen = myTCPServer->nextPendingConnection();
    if(!myTCPSocketForListen->waitForConnected(1000))
        connect(myTCPSocketForListen, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displaySocketError(QAbstractSocket::SocketError)));
    else
    {
        qDebug() << "Connected to TCP Socket : " << myTCPSocketForListen;
        ui->Label2->setText("Connected");
        //connect(myTCPSocketForListen, SIGNAL(readyRead()), this, SLOT(onReceiveDataFromClient()));
        connect(myTCPSocketForListen, SIGNAL(readyRead()), this, SLOT(onReceiveDataFromClient()));
    }
}

void MainWindow::displaySocketError(QAbstractSocket::SocketError socketError)
{

}

void MainWindow::onReceiveDataFromClient()
{
    char receiveBuffer[1024];
    int numberOfBytesAvailable;

    qDebug() << "\n======================== Reading!! ===========================";
    numberOfBytesAvailable = myTCPSocketForListen->bytesAvailable();
    qDebug() << "Bytes Available: " << numberOfBytesAvailable;

    if(numberOfBytesAvailable > 0)
    {
        if (numberOfBytesAvailable > 1024)
            numberOfBytesAvailable = 1024;
        int i = myTCPSocketForListen->read(receiveBuffer, numberOfBytesAvailable);
            receiveBuffer[i] = '\0';
        QString in(receiveBuffer);
        ui->lineEdit2->setText(in);
        ui->lineEdit2->displayText();
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
void MainWindow::connectToNewHost()
{
    connect(myTCPSocketForConnect, SIGNAL(connected()), this, SLOT(onTransmitDataToServer()));

    qDebug() << "\n ===================== Sending request ============================";
    myTCPSocketForConnect->connectToHost(QHostAddress("192.168.16.57"), 4000);
    qDebug()<< myTCPSocketForConnect->state();
}

void MainWindow::onTransmitDataToServer()
{
    qDebug() << "\n ===================== Connected ============================";
    ui->Label4->setText("Hurray!! Connected...");

    unsigned int i = myTCPSocketForConnect->write((ui->lineEdit->text()).toAscii(), (ui->lineEdit->text()).size());
    qDebug() << "Number of characters transmitted : " << i;
}
