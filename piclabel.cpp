 #include "piclabel.h"
#include<QFile>
#include<QPainter>


PicLabel::PicLabel(QWidget *parent  ) :QLabel(parent)
{
    //开启鼠标追踪：即使没有按下鼠标键，移动鼠标时也可以捕获鼠标的移动事件。
    setMouseTracking(true);

}
PicLabel::~PicLabel()
{

}

void PicLabel::SetPicPath(QString strPath)//设置图片路径
{
    m_Image = QImage(); //清空
    m_strImagePath = strPath;
    if (! m_Image.load(m_strImagePath))
    {
        //如果load失败可能是格式错误
        QFile file(strPath);
        if (file.open(QIODevice::ReadOnly))
        {
            m_Image.loadFromData(file.readAll());
        }
    }
    update();
}

void PicLabel::SetPic(QImage Image)
{
    m_Image = Image;
}


void PicLabel::paintEvent(QPaintEvent *event)
{
    // 设置一个画家painter,  在空白的tmpPixMap上进行绘制的
    QPainter painter(this);
    QPixmap tmpPixMap(this->width(), this->height());
    tmpPixMap.fill(Qt::transparent);
    painter.begin(&tmpPixMap);

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_Image.width(), this->width());
    int height = width * 1.0 / (m_Image.width() * 1.0 / m_Image.height());
    height = qMin(height, this->height());
    width = height * 1.0 * (m_Image.width() * 1.0 / m_Image.height());

    // 平移
    painter.translate(this->width() / 2 + XPtInterval, this->height() / 2 + YPtInterval);
    // 缩放
    painter.scale(ZoomValue, ZoomValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, m_Image);
    painter.end();

    m_bTempPixmap = tmpPixMap;
}

//键盘事件（按住ctrl 并滚动滚轮才可以放大或者缩小图片）
void PicLabel::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        setZoom(true);
    }
}
void  PicLabel::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        setZoom(false);
    }
}

//图片放大
void PicLabel::OnZoomInImage()
{
    ZoomValue += 0.05;
    update();
}

//图片缩小
void PicLabel::OnZoomOutImage()
{
    ZoomValue -= 0.05;
    if (ZoomValue <= 0)
    {
        ZoomValue = 0.05;
        return;
    }

    update();
}

//鼠标滚轮滚动
void PicLabel::wheelEvent(QWheelEvent *event)
{
    if (!m_bZoom)
        return;
    int value = event->angleDelta().y();
    if (value > 0)  //放大
        OnZoomInImage();
    else            //缩小
        OnZoomOutImage();

    update();
}

//鼠标双击还原图片大小事件
void PicLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    OnPresetImage();
}

//图片还原
void PicLabel::OnPresetImage()
{
    ZoomValue = 1.0;
    XPtInterval = 0;
    YPtInterval = 0;
    update();
}

//鼠标摁下
void PicLabel::mousePressEvent(QMouseEvent *event)
{
    OldPos = event->pos();
    Pressed = true;
}

//鼠标松开
void PicLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (!Pressed)//如果不是按下拖动，则显示实时坐标的rgb
    {
        m_nMovePos = event->pos();
        QRgb qRgb = m_bTempPixmap.toImage().pixel(m_nMovePos);
        emit SigColor(qRed(qRgb), qGreen(qRgb), qBlue(qRgb));
        return QWidget::mouseMoveEvent(event);
    }
    this->setCursor(Qt::SizeAllCursor);
    QPoint pos = event->pos();
    int xPtInterval = pos.x() - OldPos.x();
    int yPtInterval = pos.y() - OldPos.y();

    XPtInterval += xPtInterval;
    YPtInterval += yPtInterval;

    OldPos = pos;
    update();
}


void PicLabel::mouseReleaseEvent(QMouseEvent *event)
{
    Pressed = false;
    setCursor(Qt::ArrowCursor);
}


