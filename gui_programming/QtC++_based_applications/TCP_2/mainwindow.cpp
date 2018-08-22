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
    listenForNewClients();
}

MainWindow::~MainWindow()
{
    myTCPSocket->disconnectFromHost();
    myTCPSocket->close();

    delete myTCPSocket;
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
    myTCPSocket = myTCPServer->nextPendingConnection();
    if(!myTCPSocket->waitForConnected(1000))
        connect(myTCPSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displaySocketError(QAbstractSocket::SocketError)));
    else
    {
        qDebug() << "Connected to TCP Socket : " << myTCPSocket;
        ui->Label1->setText("Connected");
        connect(myTCPSocket, SIGNAL(readyRead()), this, SLOT(onReceiveDataFromClient()));
    }
}

void MainWindow::onStateChange(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
        case QAbstractSocket::UnconnectedState:
        {
            qDebug() << "Status: " << " -> XXXXXX Unconnected State... XXXXXX <-";
            break;
        }

        case QAbstractSocket::HostLookupState:
        {
            qDebug() << "Status: " << "Host Looking Up... ";
            break;
        }

        case QAbstractSocket::ConnectingState:
        {
            qDebug() << "Status: " << "... Connecting ...";
            break;
        }

        case QAbstractSocket::ConnectedState:
        {
            qDebug() << "Status: " << "Hurray!! Connected Finally...";

            /*const int timerReadyReadTimeOut = 3000;        // 3000 ms
            bool readStatus = myTCPSocket->waitForReadyRead(timerReadyReadTimeOut);
            if(!readStatus)
                displaySocketError(QAbstractSocket::SocketError);
            else
                onReceiveDataFromClient();*/

            break;
        }

        case QAbstractSocket::BoundState:
        {
            qDebug() << "Status: " << "->=======  Bound ========<-";
            break;
        }

        case QAbstractSocket::ClosingState:
        {
            qDebug() << "Status: " << "About to close :(";
            break;
        }

        case QAbstractSocket::ListeningState:
        {
            qDebug() << "Status: " << "Yes, I'm listening... :|";
            break;
        }

        default:
        {
            qDebug() << "Status: " << myTCPSocket->errorString();
            break;
        }
    }
}

/*void MainWindow::displaySocketError(QAbstractSocket::SocketError socketError)
{
    switch(socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
        {
            qDebug() << "Socket Error: " << "Remote Host Closed";
            break;
        }

        case QAbstractSocket::HostNotFoundError:
        {
            qDebug() << "Socket Error: " << "Host Not Found";
            break;
        }

        case QAbstractSocket::ConnectionRefusedError:
        {
            qDebug() << "Socket Error: " << ".. X .. Connection Refused .. X ..";
            break;
        }

    }
}*/

void MainWindow::displaySocketError(QAbstractSocket::SocketError)
{

}

void MainWindow::onReceiveDataFromClient()
{
    //static quint8 blockSize=0;
    char *s1;
    qDebug() << "\nReading!!";
    QDataStream in(myTCPSocket);
    in.setVersion(QDataStream::Qt_4_6);
    if (myTCPSocket->bytesAvailable())
    {
        qDebug() << "\nBytes Available = " << myTCPSocket->bytesAvailable();
        in >> s1;
        ui->Label2->setText(QString(s1));
    }
    ui->Label3->setText(s1);
    qDebug() << "String Received: " << s1;

    if(myTCPSocket->bytesAvailable() > 0)
        onReceiveDataFromClient();
}

void MainWindow::onReadyRead()
{
    if (myTCPSocket == NULL)
        return;

    if (myTCPSocket->state() != QAbstractSocket::ConnectedState)
        return;

    quint32 blockSize;
    QDataStream in(myTCPSocket);
    in.setVersion(QDataStream::Qt_4_6);

    if(blockSize == 0)
    {
        if (myTCPSocket->bytesAvailable() < (int)sizeof(quint32))
            return;
        in >> blockSize;
    }

    if(myTCPSocket->bytesAvailable() < blockSize)
        return;

    QString msgString;
    in >> msgString;
    ui->Label2->setText(msgString);
    blockSize = 0;

    if(myTCPSocket->bytesAvailable() > 0)
        onReadyRead();
}

void MainWindow::onDisconnected()
{
    if(myTCPSocket == NULL)
        return;
    myTCPSocket->abort();
}

