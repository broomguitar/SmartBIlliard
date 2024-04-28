/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_title;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget;
    QFormLayout *formLayout_3;
    QLabel *label_user;
    QLineEdit *lineEdit_user;
    QLabel *label_pwd;
    QLineEdit *lineEdit_pwd;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_login;
    QPushButton *pushButton_exit;
    QSpacerItem *verticalSpacer;
    QLabel *label_log;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(384, 381);
        Login->setStyleSheet(QString::fromUtf8("#Login\n"
"{\n"
"background-image:url(:/Imgs/loginBg.jpg);\n"
"}"));
        frame = new QFrame(Login);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(80, 60, 231, 251));
        frame->setStyleSheet(QString::fromUtf8("#frame\n"
"{ \n"
"background-image: url(:/Imgs/MainBg.jpg);\n"
"border-radius:10px;\n"
"border:1px solid rgb(85, 85, 127);\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        label_title = new QLabel(frame);
        label_title->setObjectName("label_title");
        QFont font;
        font.setPointSize(19);
        font.setBold(true);
        font.setItalic(true);
        label_title->setFont(font);
        label_title->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_title);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        widget = new QWidget(frame);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        formLayout_3 = new QFormLayout(widget);
        formLayout_3->setObjectName("formLayout_3");
        label_user = new QLabel(widget);
        label_user->setObjectName("label_user");
        QFont font1;
        font1.setPointSize(12);
        label_user->setFont(font1);
        label_user->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_user->setAlignment(Qt::AlignCenter);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_user);

        lineEdit_user = new QLineEdit(widget);
        lineEdit_user->setObjectName("lineEdit_user");
        lineEdit_user->setEnabled(true);
        lineEdit_user->setFont(font1);
        lineEdit_user->setStyleSheet(QString::fromUtf8("color: rgb(204, 204, 204);"));
        lineEdit_user->setCursorPosition(3);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, lineEdit_user);

        label_pwd = new QLabel(widget);
        label_pwd->setObjectName("label_pwd");
        label_pwd->setFont(font1);
        label_pwd->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_pwd->setAlignment(Qt::AlignCenter);

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_pwd);

        lineEdit_pwd = new QLineEdit(widget);
        lineEdit_pwd->setObjectName("lineEdit_pwd");
        lineEdit_pwd->setFont(font1);
        lineEdit_pwd->setStyleSheet(QString::fromUtf8("color: rgb(204, 204, 204);"));
        lineEdit_pwd->setEchoMode(QLineEdit::Password);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, lineEdit_pwd);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout_3->setItem(1, QFormLayout::LabelRole, verticalSpacer_5);


        verticalLayout->addWidget(widget);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        widget_3 = new QWidget(frame);
        widget_3->setObjectName("widget_3");
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName("gridLayout_2");
        pushButton_login = new QPushButton(widget_3);
        pushButton_login->setObjectName("pushButton_login");
        pushButton_login->setFont(font1);
        pushButton_login->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 0);\n"
"color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(pushButton_login, 0, 0, 1, 1);

        pushButton_exit = new QPushButton(widget_3);
        pushButton_exit->setObjectName("pushButton_exit");
        pushButton_exit->setFont(font1);
        pushButton_exit->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 85, 0);\n"
"color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(pushButton_exit, 0, 1, 1, 1);


        verticalLayout->addWidget(widget_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_log = new QLabel(frame);
        label_log->setObjectName("label_log");
        QFont font2;
        font2.setPointSize(10);
        label_log->setFont(font2);
        label_log->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 0);"));

        verticalLayout->addWidget(label_log);


        retranslateUi(Login);
        QObject::connect(pushButton_exit, &QPushButton::clicked, Login, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login", nullptr));
        label_title->setText(QCoreApplication::translate("Login", "\346\231\272\350\203\275\345\260\217\346\273\241\346\254\242\350\277\216\346\202\250", nullptr));
        label_user->setText(QCoreApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", nullptr));
        lineEdit_user->setText(QCoreApplication::translate("Login", "WJL", nullptr));
        lineEdit_user->setPlaceholderText(QCoreApplication::translate("Login", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        label_pwd->setText(QCoreApplication::translate("Login", "\345\257\206\347\240\201", nullptr));
        lineEdit_pwd->setText(QCoreApplication::translate("Login", "123456", nullptr));
        lineEdit_pwd->setPlaceholderText(QCoreApplication::translate("Login", "\345\257\206\347\240\201", nullptr));
        pushButton_login->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("Login", "\351\200\200\345\207\272", nullptr));
        label_log->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
