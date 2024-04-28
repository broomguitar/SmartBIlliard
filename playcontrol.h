#ifndef PLAYCONTROL_H
#define PLAYCONTROL_H
#include <QWidget>
#include "hikcamera.h"
QT_BEGIN_NAMESPACE
namespace Ui { class PlayControl; }
QT_END_NAMESPACE
class PlayControl : public QWidget
{
    Q_OBJECT
public:
    explicit PlayControl(QWidget *parent = nullptr);
    ~PlayControl();
    //按钮函数
private slots:
    void display_myImage(const Mat* imagePrt);
    void on_pushButton_open_clicked();


    void on_pushButton_close_clicked();

    void on_radioButton_continueMode_clicked();
    void on_radioButton_softTriggerMode_clicked();

    void on_pushButton_grabbing_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_softTrigger_clicked();



    //自定义对象
    void on_pushButton_saveJpg_clicked();

    void on_pushButton_saveBmp_clicked();
private:
    HIKCamera* m_pcHikCamera;         // 相机指针对象
public:
    int nRet;
    void* m_hGrabThread;                        // ch:取流线程句柄 | en:Grab thread handle
    bool m_bThreadState;
    bool m_bOpenDevice;                        // ch:是否打开设备 | en:Whether to open device
    bool m_bStartGrabbing;                     // ch:是否开始抓图 | en:Whether to start grabbing

    unsigned int m_nTriggerMode;                        //触发模式
    int m_bContinueStarted;                   // 开启过连续采集图像
    cv::Mat* myImage = new cv::Mat();          //用于保存相机图像的图像指针对象
    MV_SAVE_IAMGE_TYPE   m_nSaveImageType;      // ch:保存图像格式 | en:Save Image Type
protected:
    void paintEvent(QPaintEvent * paintEvent) override;
    //自定义方法
private:
    int loadDevices(unsigned int nTLayerType);
    //显示错误信息
    void showErrorMsg(QString qMessage, int nErrorNum);
    //保存图片
    int saveImage(MV_SAVE_IAMGE_TYPE m_nSaveImageType);
    static void callbackFunc(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser);
public:
    int initCamera(MV_CC_DEVICE_INFO * pDeviceInfo);
    int initCameraByIndex(int nDeviceIndex,MV_CC_DEVICE_INFO_LIST& pstDevList);
    int initCameraBySN(const char *cDeviceSN,MV_CC_DEVICE_INFO_LIST& pstDevList);
    int initCameraByIP(const char *cDeivceIP,MV_CC_DEVICE_INFO_LIST& pstDevList);
    int initCameraByName(const char *cDeviceName,MV_CC_DEVICE_INFO_LIST& pstDevList);
private:
    Ui::PlayControl *ui;
};

#endif // PLAYCONTROL_H
