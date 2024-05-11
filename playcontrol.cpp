#include "playcontrol.h"
#include "ui_playcontrol.h"
#include<QMessageBox>
#include <QFileDialog>
#include <QStringListModel>
#include "piclabel.h"
#define EXPOSURE_TIME   40000
#define FRAME           30
#define TRIGGER_ON      1
#define TRIGGER_OFF     0
#define TRIGGER_SOURCE_SOFTWARE  7
#define START_GRABBING_ON   1
#define START_GRABBING_OFF  0
#define IMAGE_NAME_LEN          64


PlayControl::PlayControl(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayControl)
{
    ui->setupUi(this);
    ui->pushButton_close->setEnabled(false);
    ui->radioButton_continueMode->setEnabled(false);
    ui->radioButton_softTriggerMode->setEnabled(false);
    ui->pushButton_grabbing->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_softTrigger->setEnabled(false);
    ui->pushButton_saveBmp->setEnabled(false);
    ui->pushButton_saveJpg->setEnabled(false);
    m_bThreadState =false;
    m_bStartGrabbing = false;
    m_bOpenDevice = false;
    m_nRet = MV_OK;
    m_hGrabThread = nullptr;
    m_bContinueStarted = 0;
    m_nSaveImageType = MV_Image_Bmp;

}

PlayControl::~PlayControl()
{
    if(m_bOpenDevice)
    {
        on_pushButton_close_clicked();
    }
    if(m_pcHikCamera)
    {
        delete m_pcHikCamera;
        m_pcHikCamera=nullptr;
    }
    if(myImage){
        delete myImage;
        myImage=nullptr;
    }
    delete ui;
}
void PlayControl::paintEvent(QPaintEvent *paintEvent)
{
    ui->label_play->resize(size());
}
//错误信息
// ch:显示错误信息 | en:Show error message
void PlayControl::showErrorMsg(QString qMessage, int nErrorNum)
{
    QString errorMsg;
    if (nErrorNum == 0)
    {
        errorMsg= qMessage;
    }
    else
    {
        errorMsg=QString("%1: Error = %2: ").arg(qMessage).arg(nErrorNum);
    }
     errorMsg +=HIKCamera::GetErrMsg(nErrorNum);
    QMessageBox::information(nullptr, "PROMPT", errorMsg ,QMessageBox::StandardButton::Yes|QMessageBox::StandardButton::No,QMessageBox::StandardButton::Yes);
}
//打开设备
void PlayControl::on_pushButton_open_clicked()
{
    if(m_pcHikCamera==nullptr){
        showErrorMsg(("Open Failure"),1);
    }
    m_nRet=m_pcHikCamera->Open();
    if(m_nRet !=MV_OK){
        showErrorMsg(("Open Failure"),1);
    }
    else{
        m_bOpenDevice=true;
        m_nRet=m_pcHikCamera->GetTriggerMode(&m_nTriggerMode);
        if(m_nTriggerMode==0){
            ui->radioButton_continueMode->setChecked(true);
        }
        else if(m_nTriggerMode==1){
            ui->radioButton_softTriggerMode->setChecked(true);
        }
        m_pcHikCamera->RegisterImageCallBack(&callbackFunc,this);
        ui->pushButton_open->setEnabled(false);
        ui->radioButton_softTriggerMode->setEnabled(true);
        ui->radioButton_continueMode->setEnabled(true);
        ui->pushButton_close->setEnabled(true);
        ui->pushButton_grabbing->setEnabled(true);
    }

}
void PlayControl::callbackFunc(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{

    PlayControl* pPlayControl=(PlayControl*)pUser;
    pPlayControl->m_pcHikCamera->ReadBuffer(*pPlayControl->myImage,pData,pFrameInfo);
    pPlayControl-> display_myImage(pPlayControl->myImage);
}
// ch:按下关闭设备按钮：关闭设备 ,包含销毁句柄
void PlayControl::on_pushButton_close_clicked()
{
    ui->pushButton_open->setEnabled(true);
    ui->pushButton_close->setEnabled(false);
    ui->pushButton_softTrigger->setEnabled(false);
    ui->pushButton_grabbing->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_saveBmp->setEnabled(false);
    ui->pushButton_saveJpg->setEnabled(false);
    ui->radioButton_continueMode->setEnabled(false);
    ui->radioButton_softTriggerMode->setEnabled(false);

    //销毁句柄
    m_bThreadState = false;
    m_pcHikCamera->StopGrabbing();
    m_pcHikCamera->Close();
    m_bStartGrabbing = false;
    m_bOpenDevice = false;
    qDebug() << m_pcHikCamera;
}

//按下连续采集按钮
void PlayControl::on_radioButton_continueMode_clicked()
{
    m_nTriggerMode = TRIGGER_OFF;
    m_pcHikCamera->SetTriggerMode(m_nTriggerMode);
    ui->pushButton_softTrigger->setEnabled(false);
}

// ch:按下触发模式按钮 | en:Click Trigger Mode button
void PlayControl::on_radioButton_softTriggerMode_clicked()
{
    m_nTriggerMode = TRIGGER_ON;
    m_pcHikCamera->SetTriggerMode(m_nTriggerMode);
    m_pcHikCamera->SetTriggerSource(TRIGGER_SOURCE_SOFTWARE);
    if(m_bContinueStarted){
    ui->pushButton_softTrigger->setEnabled(true);
    }
}

//软触发一次
void PlayControl::on_pushButton_softTrigger_clicked()
{
    ui->pushButton_saveBmp->setEnabled(true);
    ui->pushButton_saveJpg->setEnabled(true);

    if (m_bContinueStarted == 1&&m_nTriggerMode == TRIGGER_ON)
    {
        m_nRet = MV_OK;
        m_nRet = m_pcHikCamera->SoftTrigger();
       //m_pcHikCamera->ReadBuffer(*myImage);
       //display_myImage(myImage);//相机图像

    }
}


// 开始采集图像
void PlayControl::on_pushButton_grabbing_clicked()
{

    if(m_bContinueStarted == 0){
        on_pushButton_stop_clicked();
    }
    m_bContinueStarted = 1; // 为触发模式标记一下，切换触发模式时先执行停止采集图像函数

    // 图像采集控件
    ui->pushButton_grabbing->setEnabled(false);
    ui->pushButton_stop->setEnabled(true);
    if(m_nTriggerMode==1){
        ui->pushButton_softTrigger->setEnabled(true);
    }
    // 保存图像控件
    ui->pushButton_saveBmp->setEnabled(true);
    ui->pushButton_saveJpg->setEnabled(true);
    //开启相机采集
    m_pcHikCamera->StartGrabbing();
}


//停止采集
void PlayControl::on_pushButton_stop_clicked()
{
    m_pcHikCamera->StopGrabbing();
    ui->pushButton_grabbing->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_saveBmp->setEnabled(false);
    ui->pushButton_saveJpg->setEnabled(false);
    ui->pushButton_softTrigger->setEnabled(false);
}

void Pinch(Mat& img, Mat& dst, int degree)
{
    if (degree < 1) degree = 1;
    if (degree > 32) degree = 32;

    if (dst.empty())
        dst.create(img.rows, img.cols, img.type());
    dst = cv::Scalar::all(0);

    int chns = img.channels();
    int height = img.rows;
    int width = img.cols;

    int midX = width / 2;
    int midY = height / 2;
    int i, j, k;
    int X, Y, offsetX, offsetY;
    double radian, radius;  //弧和半径

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
             offsetX = j - midX;
             offsetY = i - midY;

             radian = atan2((double)offsetY, (double)offsetX);

             // 半径
             radius = sqrtf((float)(offsetX*offsetX + offsetY * offsetY));
             radius = sqrtf(radius)*degree;

             X = (int)(radius*cos(radian)) + midX;
             Y = (int)(radius*sin(radian)) + midY;

             if (X < 0) X = 0;
             if (X >= width) X = width - 1;
             if (Y < 0) Y = 0;
             if (Y >= height) Y = height - 1;

             for (k = 0; k < chns; k++)
             {
                 dst.at<Vec3b>(i, j)[k] = img.at<Vec3b>(Y, X)[k];
             }
        }
    }
}

//显示图像
void PlayControl::display_myImage(const Mat* imagePrt)
{
    cv::Mat rgb,rgb1;
    cv::cvtColor(*imagePrt, rgb, CV_BGR2RGB);
    // Pinch(rgb1,rgb,10);
    //判断是黑白、彩色图像
    QImage dispImage;
    if (rgb.channels() > 1)
    {
        dispImage =QImage((const unsigned char*)(rgb.data),
                          rgb.cols,rgb.rows,
                          rgb.cols*rgb.channels(),
                          QImage::Format_RGB888);
    }
    else
    {
        dispImage = QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_Indexed8);
    }

    dispImage = (dispImage).scaled(ui->label_play->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_play->setScaledContents(true);
    //显示图像
    ui->label_play->setPixmap(QPixmap::fromImage(dispImage));
    //ui->label_play->show();
    //    Sleep(1);
}


//保存图片
int PlayControl::saveImage(MV_SAVE_IAMGE_TYPE nSaveImageType){
    // ch:获取1张图 | en:Get one frame
    MV_FRAME_OUT_INFO_EX stImageInfo = { 0 };
    memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
    m_hSaveImageMux.lock();
    if(!m_pcHikCamera->m_pBufForSaveImage||stImageInfo.enPixelType==0){
        m_hSaveImageMux.unlock();
        return MV_E_NODATA;
    }
    unsigned int nDataLen = 0;
    m_nRet = MV_OK;
    // ch:仅在第一次保存图像时申请缓存，在 CloseDevice 时释放
    // en:Request buffer first time save image, release after CloseDevice
    if (!m_pcHikCamera->m_pBufForDriver)
    {
        unsigned int nRecvBufSize = 0;
        m_nRet = m_pcHikCamera->GetIntValue("PayloadSize", &nRecvBufSize);

        m_pcHikCamera->m_nBufSizeForDriver = nRecvBufSize;  // 一帧数据大小
        m_pcHikCamera->m_pBufForDriver = (unsigned char*)malloc(m_pcHikCamera->m_nBufSizeForDriver);
    }
    //m_nRet = m_pcHikCamera->GetOneFrameTimeout(m_pcHikCamera->m_pBufForDriver, &nDataLen, m_pcHikCamera->m_nBufSizeForDriver, &stImageInfo, 1000);
    if (MV_OK == m_nRet)
    {
        // ch:仅在第一次保存图像时申请缓存，在 CloseDevice 时释放
        // en:Request buffer first time save image, release after CloseDevice
        if (!m_pcHikCamera->m_pBufForSaveImage)
        {
            // ch:BMP图片大小：width * height * 3 + 2048(预留BMP头大小)
            // en:BMP image size: width * height * 3 + 2048 (Reserved BMP header size)
            m_pcHikCamera->m_nBufSizeForSaveImage = stImageInfo.nWidth * stImageInfo.nHeight * 3 + 2048;
            m_pcHikCamera->m_pBufForSaveImage = (unsigned char*)malloc(m_pcHikCamera->m_nBufSizeForSaveImage);

        }
        // ch:设置对应的相机参数 | en:Set camera parameter
        MV_SAVE_IMAGE_PARAM_EX stParam = { 0 };
        stParam.enImageType = nSaveImageType; // ch:需要保存的图像类型 | en:Image format to save;
        stParam.enPixelType = stImageInfo.enPixelType;  // 相机对应的像素格式 | en:Pixel format
        stParam.nBufferSize = m_pcHikCamera->m_nBufSizeForSaveImage;  // 存储节点的大小 | en:Buffer node size
        stParam.nWidth = stImageInfo.nWidth;         // 相机对应的宽 | en:Width
        stParam.nHeight = stImageInfo.nHeight;          // 相机对应的高 | en:Height
        stParam.nDataLen = stImageInfo.nFrameLen;
        stParam.pData = m_pcHikCamera->m_pBufForDriver;
        stParam.pImageBuffer = m_pcHikCamera->m_pBufForSaveImage;
        stParam.nJpgQuality = 90;       // ch:jpg编码，仅在保存Jpg图像时有效。保存BMP时SDK内忽略该参数

        m_nRet = m_pcHikCamera->SaveImage(&stParam);

        char chImageName[IMAGE_NAME_LEN] = { 0 };
        if (MV_Image_Bmp == stParam.enImageType)
        {//图片输出格式为BMP
            /*sprintf_s(chImageName, IMAGE_NAME_LEN, "Image_w%d_h%d_fn%03d_L.bmp", stImageInfo.nWidth, stImageInfo.nHeight, stImageInfo.nFrameNum);*/
            //sprintf_s(chImageName, IMAGE_NAME_LEN, "%03d_L.bmp", stImageInfo.nFrameNum);
            sprintf_s(chImageName, IMAGE_NAME_LEN, "%d-current_image.bmp", stImageInfo.nFrameNum);
        }
        else if (MV_Image_Jpeg == stParam.enImageType)
        {
            //sprintf_s(chImageName, IMAGE_NAME_LEN, "Image_w%d_h%d_fn%03d_L.bmp", stImageInfo.nWidth, stImageInfo.nHeight, stImageInfo.nFrameNum);
            sprintf_s(chImageName, IMAGE_NAME_LEN, "%d-current_image.jpg", stImageInfo.nFrameNum);
        }
        else if (MV_Image_Tif== stParam.enImageType)
        {
            //sprintf_s(chImageName, IMAGE_NAME_LEN, "Image_w%d_h%d_fn%03d_L.bmp", stImageInfo.nWidth, stImageInfo.nHeight, stImageInfo.nFrameNum);
            sprintf_s(chImageName, IMAGE_NAME_LEN, "%d-current_image.tif", stImageInfo.nFrameNum);
        }
        else if (MV_Image_Png == stParam.enImageType)
        {
            //sprintf_s(chImageName, IMAGE_NAME_LEN, "Image_w%d_h%d_fn%03d_L.bmp", stImageInfo.nWidth, stImageInfo.nHeight, stImageInfo.nFrameNum);
            sprintf_s(chImageName, IMAGE_NAME_LEN, "%d-current_image.png", stImageInfo.nFrameNum);
        }
        //qDebug() << chImageName;
        //将图片保存到指定路径
        QString filename=QFileDialog::getSaveFileName(this,tr("save Image"),chImageName);
        QByteArray ba = filename.toLatin1();
        char* Filename = ba.data(); //将QString装换为char*
        FILE* fp = fopen(Filename, "wb");//只写打开或新建一个二进制文件；只允许写数据

        fwrite(m_pcHikCamera->m_pBufForSaveImage, 1, stParam.nImageLen, fp);
        //ui->label_debug->setText("save imgs");
        fclose(fp);
    }
     m_hSaveImageMux.unlock();
    return m_nRet;
}
//图片保存为BMP
void PlayControl::on_pushButton_saveBmp_clicked()
{
    m_nRet = saveImage(MV_Image_Bmp);
    if(m_nRet != MV_OK){
        showErrorMsg("NO IMAGE",11);
    }else{
        QMessageBox::information(nullptr,"SAVE BMP","Save Image Successed",QMessageBox::Yes);
    }
}
//图片保存为JPG
void PlayControl::on_pushButton_saveJpg_clicked()
{
    m_nRet = saveImage(MV_Image_Jpeg);
    if(m_nRet != MV_OK){
        showErrorMsg("NO IMAGE",11);
    }else{
        QMessageBox::information(nullptr,"SAVE JPEG","Save Image Successed",QMessageBox::Yes);
    }
}
//图片保存为Png
void PlayControl::on_pushButton_savePng_clicked(){
    m_nRet = saveImage(MV_Image_Png);
    if(m_nRet != MV_OK){
        showErrorMsg("NO IMAGE",11);
    }else{
        QMessageBox::information(nullptr,"SAVE JPEG","Save Image Successed",QMessageBox::Yes);
    }
}
//图片保存为Tiff
void PlayControl::on_pushButton_saveTiff_clicked(){
    m_nRet = saveImage(MV_Image_Tif);
    if(m_nRet != MV_OK){
        showErrorMsg("NO IMAGE",11);
    }else{
        QMessageBox::information(nullptr,"SAVE JPEG","Save Image Successed",QMessageBox::Yes);
    }
}
int PlayControl::initCameraByIndex(int nDeviceIndex,MV_CC_DEVICE_INFO_LIST& pstDevList)
{

    if(pstDevList.nDeviceNum<nDeviceIndex+1) {
        return MV_E_NODATA;
    }
    m_pcHikCamera=new HIKCamera(pstDevList.pDeviceInfo[nDeviceIndex]);
    return 0;
}
int PlayControl::initCamera(MV_CC_DEVICE_INFO *pDeviceInfo)
{
    m_pcHikCamera=new HIKCamera(pDeviceInfo);
    return 0;
}
int PlayControl::initCameraBySN(const char *cDeviceSN,MV_CC_DEVICE_INFO_LIST& pstDevList)
{
    if(pstDevList.nDeviceNum<1) {
        return MV_E_NODATA;
    }
    for (int i = 0; i < pstDevList.nDeviceNum; ++i) {
        if(pstDevList.pDeviceInfo[i]->nTLayerType==MV_GIGE_DEVICE)
        {
            cout<<"Gige相机用户名称："<<(char*)pstDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.chUserDefinedName
                 <<"设备名称"<<(char *)pstDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.chModelName<<"相机序列号："
                 <<(char*)pstDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.chSerialNumber<<cDeviceSN;
            if(strcmp((char*)pstDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.chSerialNumber,cDeviceSN)==0)
            {
                m_pcHikCamera=new HIKCamera(pstDevList.pDeviceInfo[i]);
                break;
            }
        }
        else if(pstDevList.pDeviceInfo[i]->nTLayerType==MV_USB_DEVICE)
        {
            if(strcmp((char*)pstDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chSerialNumber,cDeviceSN)==0)
            {
                m_pcHikCamera=new HIKCamera(pstDevList.pDeviceInfo[i]);
                break;
            }
        }
        else if(pstDevList.pDeviceInfo[i]->nTLayerType==MV_CAMERALINK_DEVICE)
        {
            if(strcmp((char*)pstDevList.pDeviceInfo[i]->SpecialInfo.stCamLInfo.chSerialNumber,cDeviceSN)==0)
            {
                m_pcHikCamera=new HIKCamera(pstDevList.pDeviceInfo[i]);
                break;
            }
        }
    }

    return 0;
}

int PlayControl::initCameraByIP(const char *cDeivceIP,MV_CC_DEVICE_INFO_LIST& pstDevList)
{
    if(pstDevList.nDeviceNum<1) {
        return MV_E_NODATA;
    }
    int nTmpIP[4] = {0};unsigned int nIP=0;
    sscanf_s((char*)cDeivceIP,"%d.%d.%d.%d",&nTmpIP[0],&nTmpIP[1],&nTmpIP[2],&nTmpIP[3]);
    for(unsigned i=0;i<4;i++)
    {
        nIP += (nTmpIP[i]<<(24-(i*8))  & 0xFFFFFFFF);
    }
    for (int i = 0; i < pstDevList.nDeviceNum; ++i) {

        if(pstDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp==nIP)
        {
            m_pcHikCamera=new HIKCamera(pstDevList.pDeviceInfo[i]);
            break;
        }

    }
    return 0;
}

int PlayControl::initCameraByName(const char *cDeviceName,MV_CC_DEVICE_INFO_LIST& pstDevList)
{


    if(pstDevList.nDeviceNum<1) {
        return MV_E_NODATA;
    }
    for (int i = 0; i < pstDevList.nDeviceNum; ++i) {
        if(pstDevList.pDeviceInfo[i]->nTLayerType==MV_GIGE_DEVICE)
        {
            if(strcmp((char*)pstDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.chUserDefinedName,cDeviceName)==0||strcmp((char*)pstDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.chModelName,cDeviceName)==0)
            {
                m_pcHikCamera=new HIKCamera(pstDevList.pDeviceInfo[i]);
                break;
            }
        }
        else if(pstDevList.pDeviceInfo[i]->nTLayerType==MV_USB_DEVICE)
        {
            if(strcmp((char*)pstDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chUserDefinedName,cDeviceName)==0||strcmp((char*)pstDevList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chModelName,cDeviceName)==0)
            {
                m_pcHikCamera=new HIKCamera(pstDevList.pDeviceInfo[i]);
                break;
            }
        }
        else if(pstDevList.pDeviceInfo[i]->nTLayerType==MV_CAMERALINK_DEVICE)
        {
            if(strcmp((char*)pstDevList.pDeviceInfo[i]->SpecialInfo.stCamLInfo.chModelName,cDeviceName)==0)
            {
                m_pcHikCamera=new HIKCamera(pstDevList.pDeviceInfo[i]);
                break;
            }
        }
    }
    return 0;
}
