#include "login.h"
#include "ui_login.h"
#include<QColor>
#include<QGraphicsDropShadowEffect>
#include "sqlhelper.h"
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    SqlHelper::connect("127.0.0.1","smarterman","root","haiyan123");
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint|Qt::FramelessWindowHint);
    QGraphicsDropShadowEffect *shadow=new QGraphicsDropShadowEffect(this);
    shadow->setOffset(8);
    shadow->setColor(QColor(44,44,44,120));
    shadow->setBlurRadius(20);
    ui->setupUi(this);
    ui->frame->setGraphicsEffect(shadow);
    ui->frame->setContentsMargins(1,1,1,1);
    m_areaMovable =geometry();
    m_bPressed = false;

}

Login::~Login()
{
    delete ui;
}
void Login::on_pushButton_login_clicked()
{
    ui->label_log->clear();
    QString username=ui->lineEdit_user->text();
    QString pwd=this->ui->lineEdit_pwd->text();
    if(SqlHelper::queryUser(username.toStdString(),pwd.toStdString(),currentUser)){
        accept();
    }
    else{
        ui->label_log->setText("验证错误，重新输入");
        ui->lineEdit_user->clear();
        ui->lineEdit_user->setFocus();
        ui->lineEdit_pwd->clear();
    }

}
void Login::mousePressEvent(QMouseEvent *e)
{
    //鼠标左键
    if(e->button() == Qt::LeftButton)
    {
        m_ptPress = e->pos();
        m_bPressed = m_areaMovable.contains(m_ptPress);
    }
}

void Login::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
    {
        move(pos() + e->pos() - m_ptPress);
    }
}

void Login::mouseReleaseEvent(QMouseEvent *)
{
    m_bPressed = false;
}

//设置鼠标按下的区域
void Login::setAreaMovable(const QRect rt)
{
    if(m_areaMovable != rt)
    {
        m_areaMovable = rt;
    }
}

