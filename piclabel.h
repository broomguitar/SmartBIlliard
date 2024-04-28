#pragma once
#include <qlabel.h>
#include<QKeyEvent>
class PicLabel :public QLabel
{
    Q_OBJECT
public:
    PicLabel(QWidget *parent = Q_NULLPTR);
    ~PicLabel();

    void SetPicPath(QString strPath);//设置图片路径
    void SetPic(QImage Image); //设置图片
    void setPenWidth(int w) { m_intPenWidth=w; };
    void setZoom(bool bZoom) { m_bZoom = bZoom; }//设置是否允许滚动缩放
protected:
    void paintEvent(QPaintEvent *event) override;                        //QPaint画图
    void wheelEvent(QWheelEvent *event) override;               //鼠标滚轮滚动
    void mouseDoubleClickEvent(QMouseEvent *event) override;    //鼠标双击还原图片大小事件
    void mousePressEvent(QMouseEvent *event) override;          //鼠标摁下
    void mouseMoveEvent(QMouseEvent *event) override;           //鼠标移动
    void mouseReleaseEvent(QMouseEvent *event) override;        //鼠标放开
    //键盘事件（按住ctrl 并滚动滚轮才可以放大或者缩小图片）
    void keyPressEvent(QKeyEvent *event) override;
    void  keyReleaseEvent(QKeyEvent *event) override;

signals:
    void SigColor(int, int, int);

private slots:
    void OnZoomInImage();       //图片放大
    void OnZoomOutImage();      //图片缩小
    void OnPresetImage();       //图片还原

private:
    QImage m_Image;           //原始图片
    QPixmap m_bTempPixmap; //当前画图展示的缩放移动后的图片

    QString m_strImagePath="";  //图片全路径名

    qreal ZoomValue = 1.0;  //鼠标缩放值
    int XPtInterval = 0;    //平移X轴的值
    int YPtInterval = 0;    //平移Y轴的值
    bool Pressed = false;   //鼠标是否被摁压
    bool m_bZoom = true; //是否按住滚动缩放
    QPoint OldPos;          //旧的鼠标位置
    QPoint m_nMovePos;
    int m_intPenWidth = 1;

};


