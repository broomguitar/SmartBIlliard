#ifndef HIKCAMERA_H
#define HIKCAMERA_H
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <string>
#include "HIK/Includes/MvCameraControl.h"
using namespace std;
using namespace cv;
class HIKCamera
{
public:
   explicit HIKCamera(MV_CC_DEVICE_INFO * pDeviceInfo);
    ~HIKCamera();
    static string GetErrMsg(int nErrorNum);

    // ch:获取SDK版本号 | en:Get SDK Version
    static int GetSdkVersion(string & strVersion);
    //ch:获取支持的传输层 | en:Get supported Transport Layer
    static int EnumerateTls();

    // ch:枚举相机设备列表| en:Enumerate Device nTLayerType:MV_GIGE_DEVICE,MV_USB_DEVICE,MV_CAMERALINK_DEVICE
    static int EnumDevices(unsigned int nTLayerType,MV_CC_DEVICE_INFO_LIST* pstDevList);
    // ch:判断设备是否可达 | en:Is the device accessible
    //nAccessMode: MV_ACCESS_Exclusive,MV_ACCESS_ExclusiveWithSwitch ,MV_ACCESS_Control ,MV_ACCESS_ControlWithSwitch ,MV_ACCESS_ControlSwitchEnable  ,MV_ACCESS_ControlSwitchEnableWithKey  ,MV_ACCESS_Monitor
    bool IsDeviceAccessible(unsigned int nAccessMode);

    // ch:打开设备 | en:Open Device
    int Open();
    // ch:关闭设备 | en:Close Device
    int Close();

    // ch:判断相机是否处于连接状态 | en:Is The Device Connected
    bool IsDeviceConnected();

    // ch:注册图像数据回调 | en:Register Image Data CallBack
    int RegisterImageCallBack(void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser), void* pUser);


    // ch:开启抓图 | en:Start Grabbing
    int StartGrabbing();

    // ch:停止抓图 | en:Stop Grabbing
    int StopGrabbing();

    // ch:主动获取一帧图像数据 | en:Get one frame initiatively
    int GetImageBuffer(MV_FRAME_OUT* pFrame, int nMsec);

    // ch:主动获取一帧图像数据 | en:Get one frame initiatively
    int GetOneFrameTimeout(unsigned char* pData, unsigned int* pnDataLen, unsigned int nDataSize, MV_FRAME_OUT_INFO_EX* pFrameInfo, int nMsec);

    // ch:释放图像缓存 | en:Free image buffer
    int FreeImageBuffer(MV_FRAME_OUT* pFrame);

    // ch:显示一帧图像 | en:Display one frame image
    int DisplayOneFrame(MV_DISPLAY_FRAME_INFO* pDisplayInfo);

    // ch:设置SDK内部图像缓存节点个数 | en:Set the number of the internal image cache nodes in SDK
    int SetImageNodeNum(unsigned int nNum);

    // ch:获取设备信息 | en:Get device information
    int GetDeviceInfo(MV_CC_DEVICE_INFO* pstDevInfo);

    // ch:获取GEV相机的统计信息 | en:Get detect info of GEV camera
    int GetGevAllMatchInfo(MV_MATCH_INFO_NET_DETECT* pMatchInfoNetDetect);

    // ch:获取USB相机的统计信息 | en:Get detect info of USB camera
    int GetUSBAllMatchInfo(MV_MATCH_INFO_USB_DETECT* pMatchInfoUSBDetect);

    // ch:获取和设置Int型参数，如 Width和Height，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
    // en:Get Int type parameters, such as Width and Height, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int SetIntValue(IN const char* strKey, IN int64_t nValue);
    int GetIntValue(IN const char* strKey, OUT unsigned int* pIntValue);
    int SetEnumValue(IN const char* strKey, IN unsigned int nValue);
    int GetEnumValue(IN const char* strKey, OUT MVCC_ENUMVALUE *pEnumValue);
    int SetEnumValueByString(IN const char* strKey, IN const char* sValue);


    // ch:获取和设置Float型参数，如 ExposureTime和Gain，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件 | en:Get Float type parameters, such as ExposureTime and Gain, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int GetFloatValue(IN const char* strKey, OUT MVCC_FLOATVALUE *pFloatValue);
    int SetFloatValue(IN const char* strKey, IN float fValue);

    // ch:获取和设置Bool型参数，如 ReverseX，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件 | en:Get Bool type parameters, such as ReverseX, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int GetBoolValue(IN const char* strKey, OUT bool *pbValue);
    int SetBoolValue(IN const char* strKey, IN bool bValue);

    // ch:获取和设置String型参数，如 DeviceUserID，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件UserSetSave
    // en:Get String type parameters, such as DeviceUserID, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int GetStringValue(IN const char* strKey, MVCC_STRINGVALUE *pStringValue);
    int SetStringValue(IN const char* strKey, IN const char * strValue);

    // ch:执行一次Command型命令，如 UserSetSave，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
    // en:Execute Command once, such as UserSetSave, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int CommandExecute(IN const char* strKey);

    // ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
    int GetOptimalPacketSize(unsigned int* pOptimalPacketSize);

    // ch:注册消息异常回调 | en:Register Message Exception CallBack
    int RegisterExceptionCallBack(void(__stdcall* cbException)(unsigned int nMsgType, void* pUser), void* pUser);

    // ch:注册单个事件回调 | en:Register Event CallBack
    int RegisterEventCallBack(const char* pEventName, void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser), void* pUser);

    // ch:强制IP | en:Force IP
    int ForceIp(unsigned int nIP, unsigned int nSubNetMask, unsigned int nDefaultGateWay);
    int ForceIp(const char * cIP,const char * cSubNetMask,const char * cDefaultGateWay);
    // ch:配置IP方式 | en:IP configuration method nType: MV_IP_CFG_STATIC,MV_IP_CFG_DHCP,MV_IP_CFG_LLA
    int SetIpConfig(unsigned int nType);
    // ch:设置网络传输模式 | en:Set Net Transfer Mode nType:MV_NET_TRANS_DRIVER,MV_NET_TRANS_SOCKET
    int SetNetTransMode(unsigned int nType);

    // ch:像素格式转换 | en:Pixel format conversion
    int ConvertPixelType(MV_CC_PIXEL_CONVERT_PARAM* pstCvtParam);

    // ch:保存图片 | en:save image
    int SaveImage(MV_SAVE_IMAGE_PARAM_EX* pstParam);

    // ch:保存图片为文件 | en:Save the image as a file
    int SaveImageToFile(MV_SAVE_IMG_TO_FILE_PARAM* pstParam);

    //设置是否为触发模式 | en:Set Enum value  MV_CAM_TRIGGER_MODE:MV_TRIGGER_MODE_OFF,MV_TRIGGER_MODE_ON
    int SetTriggerMode(unsigned int nTriggerMode);
    int GetTriggerMode(unsigned int * pnTriggerMode);
    //设置触发源 MV_CAM_TRIGGER_SOURCE 枚举
    int SetTriggerSource(unsigned int nTriggerSource);
    //软触发
    int SoftTrigger();
    int SetExposureTime(float fExpValue);
    int GetExposureTime(float* fExpValue);
    int SetGain(float fGainValue);
    int GetGain(float * fGainValue);
    //读取buffer
    int ReadBuffer(cv::Mat& image);
    //读取buffer
    int ReadBuffer(cv::Mat& image,unsigned char * pData,MV_FRAME_OUT_INFO_EX *pFrameInfo);
    // ch:像素排列由RGB转为BGR | en:Convert pixel arrangement from RGB to BGR
    void RGB2BGR( unsigned char* pRgbData, unsigned int nWidth, unsigned int nHeight );

private:
    void* m_hDevHandle=nullptr;
    MV_CC_DEVICE_INFO * m_pDeviceInfo=nullptr;
public:
    unsigned int     m_nTiggerMode=MV_CAM_TRIGGER_MODE::MV_TRIGGER_MODE_OFF;
    unsigned int     m_nTriggerSource=MV_CAM_TRIGGER_SOURCE::MV_TRIGGER_SOURCE_SOFTWARE;
    // 用于保存图像的缓存
    unsigned char* m_pBufForSaveImage=nullptr;

    unsigned int m_nBufSizeForSaveImage;
    // 用于从驱动获取图像的缓存
    unsigned char* m_pBufForDriver=nullptr;

    unsigned int m_nBufSizeForDriver;

};

#endif // HIKCAMERA_H
