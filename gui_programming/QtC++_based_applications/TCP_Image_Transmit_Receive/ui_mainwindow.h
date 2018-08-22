/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 18. Aug 00:17:21 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *Label1;
    QLabel *Label2;
    QLabel *Label3;
    QLineEdit *lineEdit;
    QCommandLinkButton *commandLinkButton;
    QLabel *FixedLabel;
    QLabel *FixedLabel2;
    QLabel *Label4;
    QLineEdit *lineEdit2;
    QGraphicsView *view1;
    QGraphicsView *view2;
    QCommandLinkButton *displayButton;
    QCommandLinkButton *commandLinkButton_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Label1 = new QLabel(centralWidget);
        Label1->setObjectName(QString::fromUtf8("Label1"));
        Label1->setGeometry(QRect(350, 20, 231, 21));
        Label2 = new QLabel(centralWidget);
        Label2->setObjectName(QString::fromUtf8("Label2"));
        Label2->setGeometry(QRect(350, 50, 231, 21));
        Label3 = new QLabel(centralWidget);
        Label3->setObjectName(QString::fromUtf8("Label3"));
        Label3->setGeometry(QRect(360, 90, 221, 31));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(110, 60, 151, 41));
        commandLinkButton = new QCommandLinkButton(centralWidget);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(10, 60, 91, 41));
        FixedLabel = new QLabel(centralWidget);
        FixedLabel->setObjectName(QString::fromUtf8("FixedLabel"));
        FixedLabel->setGeometry(QRect(140, 10, 91, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        FixedLabel->setFont(font);
        FixedLabel2 = new QLabel(centralWidget);
        FixedLabel2->setObjectName(QString::fromUtf8("FixedLabel2"));
        FixedLabel2->setGeometry(QRect(430, 0, 81, 20));
        FixedLabel2->setFont(font);
        Label4 = new QLabel(centralWidget);
        Label4->setObjectName(QString::fromUtf8("Label4"));
        Label4->setGeometry(QRect(100, 30, 171, 21));
        lineEdit2 = new QLineEdit(centralWidget);
        lineEdit2->setObjectName(QString::fromUtf8("lineEdit2"));
        lineEdit2->setGeometry(QRect(380, 130, 191, 41));
        view1 = new QGraphicsView(centralWidget);
        view1->setObjectName(QString::fromUtf8("view1"));
        view1->setGeometry(QRect(90, 220, 261, 271));
        view2 = new QGraphicsView(centralWidget);
        view2->setObjectName(QString::fromUtf8("view2"));
        view2->setGeometry(QRect(380, 220, 271, 271));
        displayButton = new QCommandLinkButton(centralWidget);
        displayButton->setObjectName(QString::fromUtf8("displayButton"));
        displayButton->setGeometry(QRect(120, 160, 181, 41));
        commandLinkButton_2 = new QCommandLinkButton(centralWidget);
        commandLinkButton_2->setObjectName(QString::fromUtf8("commandLinkButton_2"));
        commandLinkButton_2->setGeometry(QRect(400, 180, 168, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        Label1->setText(QString());
        Label2->setText(QString());
        Label3->setText(QString());
        lineEdit->setText(QString());
        commandLinkButton->setText(QApplication::translate("MainWindow", "Click Here", 0, QApplication::UnicodeUTF8));
        FixedLabel->setText(QApplication::translate("MainWindow", "Transmitter End", 0, QApplication::UnicodeUTF8));
        FixedLabel2->setText(QApplication::translate("MainWindow", "Receiver End", 0, QApplication::UnicodeUTF8));
        Label4->setText(QString());
        displayButton->setText(QApplication::translate("MainWindow", "Click To Transmit Image", 0, QApplication::UnicodeUTF8));
        commandLinkButton_2->setText(QApplication::translate("MainWindow", "CommandLinkButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
