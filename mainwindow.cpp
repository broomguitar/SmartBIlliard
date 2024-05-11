#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QThread>
#include "global_wjl.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BasicGUIApp");
    this->showNormal();
    //创建显示容器
    scene = new QGraphicsScene;
    //借助graphicsView（QGraphicsView类）控件显示容器的内容
    ui->graphicsView_Img->setScene(scene);
    //开始显示
    ui->graphicsView_Img->show();
    ui->statusBar->setStyleSheet("QStatusBar::item{border: 0px;color:#ffffff}");
    QLabel *normal=new QLabel(QString::fromStdString(currentUser.UserName),this);
    normal->setFont(QFont("Microsoft YaHei", 12, QFont::Bold));
    normal->setStyleSheet("color:#ff6600");
    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    QString str = dateTime .toString("yyyy-MM-dd hh:mm:ss");//格式化时间
    timeLabel=new QLabel(str,this);
    timeLabel->setStyleSheet("color:#FFF5EE");
    timeLabel->setFont(QFont("Microsoft YaHei", 10, QFont::Bold,true));
    string versionStr;
    HIKCamera::GetSdkVersion(versionStr);
    QLabel *label_version=new QLabel(QString("SDK版本：%1").arg(QString::fromStdString(versionStr)),this);
    label_version->setStyleSheet("color:#FEFEFE");
    label_version ->setFont(QFont("Microsoft YaHei",10));
    ui->statusBar->addWidget(normal);//显示正常信息
    ui->statusBar->addWidget(timeLabel);
    ui->statusBar->addWidget(label_version);
    ui->statusBar->setSizeGripEnabled(false);//去掉状态栏右下角的三角
    ui->statusBar->showMessage(tr("临时信息!"),2000);//显示临时信息2000ms 前面的正常信息被覆盖 当去掉后一项时，会一直显示
    QLabel *permanent=new QLabel(this);
    QPalette pe;
    //"#03A89E"
    pe.setColor(QPalette::WindowText,QColor(0x03,0xA8,0x9E));
    permanent->setPalette(pe);
    permanent->setText(tr("Cogito ergo sum"));
    QFont font=QFont("Microsoft YaHei", 14, QFont::Bold,true);
    permanent->setFont(font);
    //permanent->setOpenExternalLinks(true);//设置可以打开网站链接
    ui->statusBar->addPermanentWidget(permanent);//显示永久信息
    loadDevices(MV_GIGE_DEVICE|MV_USB_DEVICE,&m_pstDevList);
    clockTimer=new QTimer();
    clockTimer->setInterval(1000);
    connect(clockTimer,SIGNAL(timeout()),this,SLOT(on_TimeOut()));
    clockTimer->start();
    m_PlayControl=new PlayControl(ui->widget_2);
    m_PlayControl->initCamera(m_pstDevList.pDeviceInfo[0]);//"00E06252277",
    m_PlayControl->setGeometry(QRect(0,0,10,10));
    m_PlayControl->show();
    m_PlayControl1=new PlayControl(ui->widget_4);
    m_PlayControl1->initCamera(m_pstDevList.pDeviceInfo[1]);//"00D70349387"
    m_PlayControl1->setGeometry(QRect(0,0,10,10));
    m_PlayControl1->show();

}

MainWindow::~MainWindow()
{
    delete clockTimer;
    delete timeLabel;
    delete scene;
    delete m_PlayControl;
    delete m_PlayControl1;
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *paintEvent)
{
    ui->label_play->resize(ui->widget->size());
    ui->graphicsView_Img->resize(ui->widget_3->size());
    m_PlayControl->resize(ui->widget_2->size());
     m_PlayControl1->resize(ui->widget_4->size());
}
void MainWindow::closeEvent(QCloseEvent *event)
{

}
void MainWindow::on_TimeOut()
{
    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间

    QString str = dateTime .toString("yyyy-MM-dd hh:mm:ss");//格式化时间
    timeLabel->clear();
    timeLabel->setText(str);

}
int MainWindow::loadDevices(unsigned int nTLayerType, MV_CC_DEVICE_INFO_LIST * pstDevList)
{
    return HIKCamera::EnumDevices(nTLayerType,pstDevList);
}
