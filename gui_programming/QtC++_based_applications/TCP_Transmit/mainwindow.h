#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);


private:
    Ui::MainWindow *ui;
    QTcpServer *myTCPServer;
    QTcpSocket *myTCPSocketForListen;
    QTcpSocket *myTCPSocketForConnect;

private slots:
    //void onStateChange(QAbstractSocket::SocketState);
    void displaySocketError(QAbstractSocket::SocketError);

    void listenForNewClients();
    void connectToNextPendingClient();
    void onReceiveDataFromClient();

    void connectToNewHost();
    void onTransmitDataToServer();
};

#endif // MAINWINDOW_H
