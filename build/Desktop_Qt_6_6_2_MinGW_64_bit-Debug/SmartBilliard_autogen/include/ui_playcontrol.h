/********************************************************************************
** Form generated from reading UI file 'PlayControl.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYCONTROL_H
#define UI_PLAYCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayControl
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_2;
    QLabel *label_play;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_open;
    QPushButton *pushButton_close;
    QRadioButton *radioButton_continueMode;
    QRadioButton *radioButton_softTriggerMode;
    QPushButton *pushButton_grabbing;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_softTrigger;
    QPushButton *pushButton_saveBmp;
    QPushButton *pushButton_saveJpg;

    void setupUi(QWidget *PlayControl)
    {
        if (PlayControl->objectName().isEmpty())
            PlayControl->setObjectName("PlayControl");
        PlayControl->resize(739, 520);
        verticalLayout_3 = new QVBoxLayout(PlayControl);
        verticalLayout_3->setObjectName("verticalLayout_3");
        widget_2 = new QWidget(PlayControl);
        widget_2->setObjectName("widget_2");
        label_play = new QLabel(widget_2);
        label_play->setObjectName("label_play");
        label_play->setGeometry(QRect(9, 9, 16, 16));

        verticalLayout_3->addWidget(widget_2);

        widget = new QWidget(PlayControl);
        widget->setObjectName("widget");
        widget->setEnabled(true);
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_open = new QPushButton(widget);
        pushButton_open->setObjectName("pushButton_open");

        horizontalLayout->addWidget(pushButton_open);

        pushButton_close = new QPushButton(widget);
        pushButton_close->setObjectName("pushButton_close");

        horizontalLayout->addWidget(pushButton_close);

        radioButton_continueMode = new QRadioButton(widget);
        radioButton_continueMode->setObjectName("radioButton_continueMode");
        radioButton_continueMode->setChecked(true);

        horizontalLayout->addWidget(radioButton_continueMode);

        radioButton_softTriggerMode = new QRadioButton(widget);
        radioButton_softTriggerMode->setObjectName("radioButton_softTriggerMode");

        horizontalLayout->addWidget(radioButton_softTriggerMode);

        pushButton_grabbing = new QPushButton(widget);
        pushButton_grabbing->setObjectName("pushButton_grabbing");

        horizontalLayout->addWidget(pushButton_grabbing);

        pushButton_stop = new QPushButton(widget);
        pushButton_stop->setObjectName("pushButton_stop");

        horizontalLayout->addWidget(pushButton_stop);

        pushButton_softTrigger = new QPushButton(widget);
        pushButton_softTrigger->setObjectName("pushButton_softTrigger");

        horizontalLayout->addWidget(pushButton_softTrigger);

        pushButton_saveBmp = new QPushButton(widget);
        pushButton_saveBmp->setObjectName("pushButton_saveBmp");

        horizontalLayout->addWidget(pushButton_saveBmp);

        pushButton_saveJpg = new QPushButton(widget);
        pushButton_saveJpg->setObjectName("pushButton_saveJpg");

        horizontalLayout->addWidget(pushButton_saveJpg);


        verticalLayout_3->addWidget(widget);

        verticalLayout_3->setStretch(0, 9);
        verticalLayout_3->setStretch(1, 1);

        retranslateUi(PlayControl);

        QMetaObject::connectSlotsByName(PlayControl);
    } // setupUi

    void retranslateUi(QWidget *PlayControl)
    {
        PlayControl->setWindowTitle(QCoreApplication::translate("PlayControl", "Form", nullptr));
        label_play->setText(QString());
        pushButton_open->setText(QCoreApplication::translate("PlayControl", "\346\211\223\345\274\200", nullptr));
        pushButton_close->setText(QCoreApplication::translate("PlayControl", "\345\205\263\351\227\255", nullptr));
        radioButton_continueMode->setText(QCoreApplication::translate("PlayControl", "\350\277\236\347\273\255\351\207\207\351\233\206", nullptr));
        radioButton_softTriggerMode->setText(QCoreApplication::translate("PlayControl", "\350\275\257\350\247\246\345\217\221", nullptr));
        pushButton_grabbing->setText(QCoreApplication::translate("PlayControl", "\351\207\207\351\233\206", nullptr));
        pushButton_stop->setText(QCoreApplication::translate("PlayControl", "\345\201\234\346\255\242", nullptr));
        pushButton_softTrigger->setText(QCoreApplication::translate("PlayControl", "\350\275\257\350\247\246\345\217\221", nullptr));
        pushButton_saveBmp->setText(QCoreApplication::translate("PlayControl", "\344\277\235\345\255\230BMP", nullptr));
        pushButton_saveJpg->setText(QCoreApplication::translate("PlayControl", "\344\277\235\345\255\230JPG", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayControl: public Ui_PlayControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYCONTROL_H
