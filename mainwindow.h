#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QTimer>
#include<QLabel>
#include <QGraphicsScene>
#include "playcontrol.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent * paintEvent) override;
    void closeEvent(QCloseEvent *event) override;
private slots:  
    void on_TimeOut();
private:
        MV_CC_DEVICE_INFO_LIST m_pstDevList;
private:
        int loadDevices(unsigned int nTLayerType, MV_CC_DEVICE_INFO_LIST * pstDevList);
private:
    Ui::MainWindow *ui;
    QTimer *clockTimer;
    QLabel *timeLabel;
    QGraphicsScene *scene;
    PlayControl * m_PlayControl;
    PlayControl * m_PlayControl1;
};
#endif // MAINWINDOW_H
