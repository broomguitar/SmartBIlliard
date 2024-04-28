/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget_2;
    QWidget *widget;
    QLabel *label_play;
    QWidget *widget_4;
    QWidget *widget_3;
    QGraphicsView *graphicsView_Img;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("#MainWindow\n"
"{\n"
"border-image: url(:/Imgs/MainBg.jpg);\n"
"}\n"
"\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        widget_2->setStyleSheet(QString::fromUtf8("#widget_2\n"
"{\n"
"	background-color: rgb(85, 85, 127);\n"
"}"));

        gridLayout->addWidget(widget_2, 0, 1, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8(""));
        label_play = new QLabel(widget);
        label_play->setObjectName("label_play");
        label_play->setEnabled(true);
        label_play->setGeometry(QRect(0, 0, 16, 16));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName("widget_4");

        gridLayout->addWidget(widget_4, 1, 1, 1, 1);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName("widget_3");
        graphicsView_Img = new QGraphicsView(widget_3);
        graphicsView_Img->setObjectName("graphicsView_Img");
        graphicsView_Img->setGeometry(QRect(0, 0, 401, 251));

        gridLayout->addWidget(widget_3, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 900, 21));
        menuBar->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_play->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
