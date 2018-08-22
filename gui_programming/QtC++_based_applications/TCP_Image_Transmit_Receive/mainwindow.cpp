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
#include <QByteArray>
#include <QDataStream>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QImage>
#include <QImageWriter>

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
        qDebug() << "\n=================== Connected =======================";
        qDebug() << "\nConnected to TCP Socket : " << myTCPSocketForListen;
        ui->Label2->setText("Connected");
        connect(myTCPSocketForListen, SIGNAL(readyRead()), this, SLOT(onReceiveDataFromClient()));
    }
}

void MainWindow::displaySocketError(QAbstractSocket::SocketError socketError)
{

}

void MainWindow::onReceiveDataFromClient()
{
    QFile myFile("C://Users/P V S/Desktop/1.jpg");
    myFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QDataStream in(&myFile);

    int numberOfBytesAvailable = 0;

    qDebug() << "\n======================== Reading!! ===========================";
    numberOfBytesAvailable = myTCPSocketForListen->bytesAvailable();

    if(numberOfBytesAvailable > 0)
    {
        qDebug() << "\nBytes Available: " << numberOfBytesAvailable;
        in << myTCPSocketForListen->readAll();
    }
    in.device()->seek(0);
    myFile.close();
}

// ---------------------------------------------------------------------------------------------------------------------------
void MainWindow::connectToNewHost()
{
    connect(myTCPSocketForConnect, SIGNAL(connected()), this, SLOT(onTransmitDataToServer()));

    qDebug() << "\n ========== SocketForConnect Sending request ===========";
    myTCPSocketForConnect->connectToHost(QHostAddress("192.168.1.11"), 4000);
    qDebug()<< myTCPSocketForConnect->state();
    connect(myTCPSocketForConnect, SIGNAL(connected()), this, SLOT(connectionWithHostEstablished()));
}

void MainWindow::connectionWithHostEstablished()
{

    qDebug() << "\n ===================== Connected ============================";
    ui->Label4->setText("Hurray!! Connected...");
}

void MainWindow::onTransmitDataToServer()
{
    unsigned int i = myTCPSocketForConnect->write((ui->lineEdit->text()).toAscii(), (ui->lineEdit->text()).size());
    qDebug() << "\nNumber of characters transmitted : " << i;
}

void MainWindow::on_displayButton_clicked()
{
    QFile transmitFileName("C://Users/P V S/Desktop/pics/Frangipani Flowers.jpg");
    transmitFileName.open(QIODevice::ReadOnly);

    QByteArray myByteArray1;
    myByteArray1 = transmitFileName.readAll();

    QBuffer buffer(&myByteArray1);
    buffer.open(QIODevice::WriteOnly);

    qDebug() << "\n------------------ Preparing to Send ------------------";
    qDebug() <<  "Buffer Size to Send: " << buffer.size();

    myTCPSocketForConnect->write(myByteArray1.data(), buffer.size());

    qDebug() << "\n================== Data Transmitted ====================";
    transmitFileName.close();
}

void MainWindow::on_commandLinkButton_2_clicked()
{

}
