#include "hikcamera.h"
HIKCamera::HIKCamera(MV_CC_DEVICE_INFO * pDeviceInfo):m_pDeviceInfo(pDeviceInfo){
    m_hDevHandle=nullptr;

};
HIKCamera::~HIKCamera(){
    if(m_hDevHandle){
        MV_CC_DestroyHandle(m_hDevHandle);    
        m_hDevHandle=nullptr;
    }
}

string HIKCamera::GetErrMsg(int nErrorNum)
{
    string errorMsg;
    switch(nErrorNum)
    {
    case 0:     errorMsg+="Success";                                                            break;
    case 1:     errorMsg += "Error or invalid handle ";                                         break;
    case 2:     errorMsg += "Not supported function ";                                          break;
    case 3:     errorMsg += "Cache is full ";                                                   break;
    case 4:     errorMsg += "Function calling order error ";                                    break;
    case 5:     errorMsg += "Incorrect parameter ";                                             break;
    case 6:     errorMsg += "Applying resource failed ";                                        break;
    case 7:     errorMsg += "No data ";                                                         break;
    case 8:     errorMsg += "Precondition error, or running environment changed ";              break;
    case 9:     errorMsg += "Version mismatches ";                                              break;
    case 10:    errorMsg += "Insufficient memory ";                                             break;
    case 11:    errorMsg += "Abnormal image, maybe incomplete image because of lost packet ";   break;
    case 12:    errorMsg += "Unknown error ";                                                   break;
    case 13:    errorMsg += "General error ";                                                   break;
    case 14:    errorMsg += "Node accessing condition error ";                                  break;
    case 15:    errorMsg += "No permission ";                                                   break;
    case 16:    errorMsg += "Device is busy, or network disconnected ";                         break;
    case 17:    errorMsg += "Network error ";                                                   break;
    }
    return errorMsg;
}
int HIKCamera::GetSdkVersion(string & strVersion){
    unsigned int version= MV_CC_GetSDKVersion();
    int main = ((version & 0xff000000) >> 24);
    int sub = ((version & 0x00ff0000) >> 16);
    int rev = ((version & 0x0000ff00) >> 8);
    int test = (version & 0x000000ff);
    std::stringstream ss;
    ss << "V"<< main<<"."<<sub<<"."<<rev<<"."<<test;
    strVersion=ss.str();
    return version;
}

int HIKCamera::EnumerateTls()
{
    return MV_CC_EnumerateTls();
}
int HIKCamera::EnumDevices(unsigned int nTLayerType, MV_CC_DEVICE_INFO_LIST * pstDevList){
    return MV_CC_EnumDevices(nTLayerType,pstDevList);
}
bool HIKCamera::IsDeviceAccessible(unsigned int nAccessMode){
    if(m_pDeviceInfo==nullptr){
        return MV_E_PARAMETER;
    }
    return MV_CC_IsDeviceAccessible(m_pDeviceInfo,nAccessMode);
}
int HIKCamera::Open(){
    if(!m_pDeviceInfo){
        return MV_E_PARAMETER;
    }
    if(m_hDevHandle){
        return MV_E_CALLORDER;
    }
    if(m_pDeviceInfo->nTLayerType==MV_GIGE_DEVICE)
    {
        cout<<"Gige相机用户名称："<<(char*)m_pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName<<"设备名称"<<(char *)m_pDeviceInfo->SpecialInfo.stGigEInfo.chModelName<<"相机序列号："<<(char*)m_pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber<<endl;
    }
    else if(m_pDeviceInfo->nTLayerType==MV_USB_DEVICE)
    {
        cout<<"USB相机用户名称："<<(char*)m_pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName<<"设备名称"<<(char *)m_pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName<<"相机序列号："<<(char*)m_pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber<<endl;
    }
    else if(m_pDeviceInfo->nTLayerType==MV_CAMERALINK_DEVICE)
    {
        cout<<"CameraLink相机家族名称："<<(char*)m_pDeviceInfo->SpecialInfo.stCamLInfo.chFamilyName<<"设备名称"<<(char *)m_pDeviceInfo->SpecialInfo.stCamLInfo.chModelName<<"相机序列号："<<(char*)m_pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber<<endl;
    }
    int nRet  = MV_CC_CreateHandle(&m_hDevHandle, m_pDeviceInfo);
    if (MV_OK != nRet){
        return nRet;
    }
    nRet = MV_CC_OpenDevice(m_hDevHandle);
    if (MV_OK != nRet){
        MV_CC_DestroyHandle(m_hDevHandle);
        m_hDevHandle = nullptr;
    }

    return nRet;
}
int HIKCamera::Close(){
    if(!m_hDevHandle){
        return MV_E_HANDLE;
    }
    if (m_pBufForSaveImage)
    {
        free(m_pBufForSaveImage);
        m_pBufForSaveImage = nullptr;
    }
    MV_CC_CloseDevice(m_hDevHandle);
    int nRet=MV_CC_DestroyHandle(m_hDevHandle);
    m_hDevHandle=nullptr;
    return nRet;
}
bool HIKCamera::IsDeviceConnected(){
    return MV_CC_IsDeviceConnected(m_hDevHandle);
}
int HIKCamera::RegisterImageCallBack(void(__stdcall *cbOutput)(unsigned char * pData,MV_FRAME_OUT_INFO_EX *pFrameInfo,void *pUser),void *pUser){
    return MV_CC_RegisterImageCallBackEx(m_hDevHandle,cbOutput,pUser);
}
int HIKCamera::StartGrabbing(){
    return MV_CC_StartGrabbing(m_hDevHandle);
}
int HIKCamera::StopGrabbing(){
    return MV_CC_StopGrabbing(m_hDevHandle);
}
int HIKCamera::GetImageBuffer(MV_FRAME_OUT * pFrame,int nMsec){
    return MV_CC_GetImageBuffer(m_hDevHandle, pFrame, nMsec);
}
int HIKCamera::GetOneFrameTimeout(unsigned char* pData, unsigned int* pnDataLen, unsigned int nDataSize, MV_FRAME_OUT_INFO_EX* pFrameInfo, int nMsec){
    if(pnDataLen){
        return MV_E_PARAMETER;
    }
    int nRet=MV_OK;
    *pnDataLen=0;
    nRet = MV_CC_GetOneFrameTimeout(m_hDevHandle, pData, nDataSize, pFrameInfo, nMsec);
    if(nRet!=MV_OK){
        return nRet;
    }
    *pnDataLen=pFrameInfo->nFrameLen;
    return nRet;
}
int HIKCamera::FreeImageBuffer(MV_FRAME_OUT * pFrame){
    return MV_CC_FreeImageBuffer(m_hDevHandle,pFrame);
}
int HIKCamera::DisplayOneFrame(MV_DISPLAY_FRAME_INFO* pDisplayInfo){
    return MV_CC_DisplayOneFrame(m_hDevHandle, pDisplayInfo);
}
int HIKCamera::SetImageNodeNum(unsigned int nNum){
    return MV_CC_SetImageNodeNum(m_hDevHandle, nNum);
}
int HIKCamera::GetDeviceInfo(MV_CC_DEVICE_INFO* pstDevInfo)
{
    return MV_CC_GetDeviceInfo(m_hDevHandle, pstDevInfo);
}
int HIKCamera::GetGevAllMatchInfo(MV_MATCH_INFO_NET_DETECT* pMatchInfoNetDetect)
{
    if (nullptr == pMatchInfoNetDetect)
    {
        return MV_E_PARAMETER;
    }

    MV_CC_DEVICE_INFO stDevInfo = {0};
    GetDeviceInfo(&stDevInfo);
    if (stDevInfo.nTLayerType != MV_GIGE_DEVICE)
    {
        return MV_E_SUPPORT;
    }

    MV_ALL_MATCH_INFO struMatchInfo = {0};

    struMatchInfo.nType = MV_MATCH_TYPE_NET_DETECT;
    struMatchInfo.pInfo = pMatchInfoNetDetect;
    struMatchInfo.nInfoSize = sizeof(MV_MATCH_INFO_NET_DETECT);
    memset(struMatchInfo.pInfo, 0, sizeof(MV_MATCH_INFO_NET_DETECT));

    return MV_CC_GetAllMatchInfo(m_hDevHandle, &struMatchInfo);
}
int HIKCamera::GetUSBAllMatchInfo(MV_MATCH_INFO_USB_DETECT* pMatchInfoUSBDetect)
{
    if (nullptr == pMatchInfoUSBDetect)
    {
        return MV_E_PARAMETER;
    }

    MV_CC_DEVICE_INFO stDevInfo = {0};
    GetDeviceInfo(&stDevInfo);
    if (stDevInfo.nTLayerType != MV_USB_DEVICE)
    {
        return MV_E_SUPPORT;
    }

    MV_ALL_MATCH_INFO struMatchInfo = {0};

    struMatchInfo.nType = MV_MATCH_TYPE_USB_DETECT;
    struMatchInfo.pInfo = pMatchInfoUSBDetect;
    struMatchInfo.nInfoSize = sizeof(MV_MATCH_INFO_USB_DETECT);
    memset(struMatchInfo.pInfo, 0, sizeof(MV_MATCH_INFO_USB_DETECT));

    return MV_CC_GetAllMatchInfo(m_hDevHandle, &struMatchInfo);
}
int HIKCamera::GetIntValue(IN const char* strKey, OUT unsigned int* pnValue)
{
    if (nullptr == strKey || nullptr == pnValue)
    {
        return MV_E_PARAMETER;
    }

    MVCC_INTVALUE stParam;
    memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    int nRet = MV_CC_GetIntValue(m_hDevHandle, strKey, &stParam);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    *pnValue = stParam.nCurValue;

    return MV_OK;
}
int HIKCamera::SetIntValue(IN const char* strKey, IN int64_t nValue)
{
    return MV_CC_SetIntValueEx(m_hDevHandle, strKey, nValue);
}
int HIKCamera::GetEnumValue(IN const char* strKey, OUT MVCC_ENUMVALUE *pEnumValue){
    if (nullptr == strKey || nullptr == pEnumValue){
        return MV_E_PARAMETER;
    }

    MVCC_ENUMVALUE stParam;
    memset(&stParam, 0, sizeof(MVCC_ENUMVALUE));
    int nRet = MV_CC_GetEnumValue(m_hDevHandle, strKey, pEnumValue);
    if (MV_OK != nRet){
        return nRet;
    }

    //     *pEnumValue = stParam.nCurValue;

    return nRet;
}

int HIKCamera::SetEnumValue(IN const char* strKey, IN unsigned int nValue)
{
    return MV_CC_SetEnumValue(m_hDevHandle, strKey, nValue);
}

int HIKCamera::SetEnumValueByString(IN const char* strKey, IN const char* sValue)
{
    return MV_CC_SetEnumValueByString(m_hDevHandle, strKey, sValue);
}
int HIKCamera::GetFloatValue(IN const char* strKey, OUT MVCC_FLOATVALUE *pFloatValue)
{
    return MV_CC_GetFloatValue(m_hDevHandle, strKey, pFloatValue);
}
int HIKCamera::SetFloatValue(IN const char* strKey, IN float fValue)
{
    return MV_CC_SetFloatValue(m_hDevHandle, strKey, fValue);
}
int HIKCamera::GetBoolValue(IN const char* strKey, OUT bool *pbValue)
{
    return MV_CC_GetBoolValue(m_hDevHandle, strKey, pbValue);
}
int HIKCamera::SetBoolValue(IN const char* strKey, IN bool bValue)
{
    return MV_CC_SetBoolValue(m_hDevHandle, strKey, bValue);
}
int HIKCamera::GetStringValue(IN const char* strKey, MVCC_STRINGVALUE *pStringValue)
{
    return MV_CC_GetStringValue(m_hDevHandle, strKey, pStringValue);
}
int HIKCamera::SetStringValue(IN const char* strKey, IN const char* strValue)
{
    return MV_CC_SetStringValue(m_hDevHandle, strKey, strValue);
}
int HIKCamera::CommandExecute(IN const char* strKey)
{
    return MV_CC_SetCommandValue(m_hDevHandle, strKey);
}
int HIKCamera::GetOptimalPacketSize(unsigned int* pOptimalPacketSize)
{
    if (nullptr == pOptimalPacketSize)
    {
        return MV_E_PARAMETER;
    }

    int nRet = MV_CC_GetOptimalPacketSize(m_hDevHandle);
    if (nRet < MV_OK)
    {
        return nRet;
    }

    *pOptimalPacketSize = (unsigned int)nRet;

    return MV_OK;
}
int HIKCamera::RegisterExceptionCallBack(void(__stdcall* cbException)(unsigned int nMsgType, void* pUser),void* pUser)
{
    return MV_CC_RegisterExceptionCallBack(m_hDevHandle, cbException, pUser);
}

// ch:注册单个事件回调 | en:Register Event CallBack
int HIKCamera::RegisterEventCallBack(const char* pEventName, void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser), void* pUser)
{
    return MV_CC_RegisterEventCallBackEx(m_hDevHandle, pEventName, cbEvent, pUser);
}

// ch:强制IP | en:Force IP
int HIKCamera::ForceIp(unsigned int nIP, unsigned int nSubNetMask, unsigned int nDefaultGateWay)
{
    return MV_GIGE_ForceIpEx(m_hDevHandle, nIP, nSubNetMask, nDefaultGateWay);
}
int HIKCamera::ForceIp(const char * cIP, const char * cSubNetMask, const char * cDefaultGateWay)
{
    if(cIP==nullptr||cIP[0]=='\0'||cSubNetMask==nullptr||cSubNetMask[0]=='\0'||cDefaultGateWay==nullptr||cDefaultGateWay[0]=='\0')
    {
        return MV_E_PARAMETER;
    }
    int nTmpIP[4] = {0};unsigned int nIP=0;
    sscanf_s(cIP,"%d.%d.%d.%d",&nTmpIP[0],&nTmpIP[1],&nTmpIP[2],&nTmpIP[3]);
    int nTmpMask[4] = {0};unsigned int nSubNetMask=0;
    sscanf_s(cSubNetMask,"%d.%d.%d.%d",&nTmpMask[0],&nTmpMask[1],&nTmpMask[2],&nTmpMask[3]);
    int nTmpGateway[4] = {0};unsigned int nDefaultGateWay=0;
    sscanf_s(cDefaultGateWay,"%d.%d.%d.%d",&nTmpGateway[0],&nTmpGateway[1],&nTmpGateway[2],&nTmpGateway[3]);
    for(unsigned i=0;i<4;i++)
    {
        nIP += (nTmpIP[i]<<(24-(i*8))  & 0xFFFFFFFF);
        nSubNetMask += (nTmpMask[i]<<(24-(i*8))  & 0xFFFFFFFF);
        nDefaultGateWay += (nTmpGateway[i]<<(24-(i*8))  & 0xFFFFFFFF);
    }
    return MV_GIGE_ForceIpEx(m_hDevHandle, nIP, nSubNetMask, nDefaultGateWay);
}

// ch:配置IP方式 | en:IP configuration method
int HIKCamera::SetIpConfig(unsigned int nType)
{
    return MV_GIGE_SetIpConfig(m_hDevHandle, nType);
}

// ch:设置网络传输模式 | en:Set Net Transfer Mode
int HIKCamera::SetNetTransMode(unsigned int nType)
{
    return MV_GIGE_SetNetTransMode(m_hDevHandle, nType);
}

// ch:像素格式转换 | en:Pixel format conversion
int HIKCamera::ConvertPixelType(MV_CC_PIXEL_CONVERT_PARAM* pstCvtParam)
{
    return MV_CC_ConvertPixelType(m_hDevHandle, pstCvtParam);
}

// ch:保存图片 | en:save image
int HIKCamera::SaveImage(MV_SAVE_IMAGE_PARAM_EX* pstParam)
{
    return MV_CC_SaveImageEx2(m_hDevHandle, pstParam);
}

// ch:保存图片为文件 | en:Save the image as a file
int HIKCamera::SaveImageToFile(MV_SAVE_IMG_TO_FILE_PARAM* pstSaveFileParam)
{
    return MV_CC_SaveImageToFile(m_hDevHandle, pstSaveFileParam);
}

//设置是否为触发模式
int HIKCamera::SetTriggerMode(unsigned int nTriggerMode)
{
    int ret = MV_CC_SetEnumValue(m_hDevHandle, "TriggerMode", nTriggerMode);
    if (ret != 0){
        return -1;
    }
    else {
        return 0;
    }
}

int HIKCamera::GetTriggerMode(unsigned int *pnTriggerMode)
{
    MVCC_ENUMVALUE enumValue;
    int ret = MV_CC_GetEnumValue(m_hDevHandle, "TriggerMode", &enumValue);
    if (ret != 0){
        return -1;
    }
    else {
        *pnTriggerMode=enumValue.nCurValue;
        return 0;
    }
}
//设置触发源
int HIKCamera::SetTriggerSource(unsigned int nTriggerSource)
{
    int ret = MV_CC_SetEnumValue(m_hDevHandle, "TriggerSource", nTriggerSource);
    if (ret != 0) {
        return -1;
    }
    else {
        return 0;
    }
}

//发送软触发
int HIKCamera::SoftTrigger()
{
    int ret = MV_CC_SetCommandValue(m_hDevHandle, "TriggerSoftware");
    if (ret != 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int HIKCamera::SetExposureTime(float fExpValue)
{
    int ret = MV_CC_SetFloatValue(m_hDevHandle, "ExposureTime", fExpValue);
    if (ret != 0){
        return -1;
    }
    else {
        return 0;
    }
}

int HIKCamera::GetExposureTime(float *fExpValue)
{
    MVCC_FLOATVALUE floatValue;
    int ret = MV_CC_GetFloatValue(m_hDevHandle, "ExposureTime", &floatValue);
    if (ret != 0){
        return -1;
    }
    else {
        *fExpValue=floatValue.fCurValue;
        return 0;
    }
}

int HIKCamera::SetGain(float fGainValue)
{
    int ret = MV_CC_SetFloatValue(m_hDevHandle, "Gain", fGainValue);
    if (ret != 0){
        return -1;
    }
    else {
        return 0;
    }
}

int HIKCamera::GetGain(float *fGainValue)
{
    MVCC_FLOATVALUE floatValue;
    int ret = MV_CC_GetFloatValue(m_hDevHandle, "Gain", &floatValue);
    if (ret != 0){
        return -1;
    }
    else {
        *fGainValue=floatValue.fCurValue;
        return 0;
    }

}

//读取相机中的图像
int HIKCamera::ReadBuffer(cv::Mat& image)
{
    cv::Mat* getImage = new cv::Mat();
    unsigned int nRecvBufSize = 0;
    MVCC_INTVALUE stParam;
    memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    int ret = MV_CC_GetIntValue(m_hDevHandle, "PayloadSize", &stParam);
    if (ret != 0)
    {
        return -1;
    }
    nRecvBufSize = stParam.nCurValue;
    unsigned char* pData;
    pData = (unsigned char*)malloc(nRecvBufSize);

    MV_FRAME_OUT_INFO_EX stImageInfo = { 0 };
    ret = MV_CC_GetOneFrameTimeout(m_hDevHandle, pData, nRecvBufSize, &stImageInfo, 500);
    if (ret != 0)
    {
        return -1;
    }
    m_nBufSizeForSaveImage = stImageInfo.nWidth * stImageInfo.nHeight * 3 + 2048;
    if (m_pBufForSaveImage)
    {
        free(m_pBufForSaveImage);
        m_pBufForSaveImage = nullptr;
    }
    m_pBufForSaveImage = (unsigned char*)malloc(m_nBufSizeForSaveImage);


    bool isMono;
    switch (stImageInfo.enPixelType)
    {
    case PixelType_Gvsp_Mono8:
    case PixelType_Gvsp_Mono10:
    case PixelType_Gvsp_Mono10_Packed:
    case PixelType_Gvsp_Mono12:
    case PixelType_Gvsp_Mono12_Packed:
        isMono = true;
        break;
    default:
        isMono = false;
        break;
    }
    if (isMono)
    {
        *getImage = cv::Mat(stImageInfo.nHeight, stImageInfo.nWidth, CV_8UC1, pData);
    }
    else
    {
        //转换图像格式为BGR8
        MV_CC_PIXEL_CONVERT_PARAM stConvertParam = { 0 };
        memset(&stConvertParam, 0, sizeof(MV_CC_PIXEL_CONVERT_PARAM));
        stConvertParam.nWidth = stImageInfo.nWidth;                 //ch:图像宽 | en:image width
        stConvertParam.nHeight = stImageInfo.nHeight;               //ch:图像高 | en:image height
        //stConvertParam.pSrcData = m_pBufForDriver;                  //ch:输入数据缓存 | en:input data buffer
        stConvertParam.pSrcData = pData;                  //ch:输入数据缓存 | en:input data buffer
        stConvertParam.nSrcDataLen = stImageInfo.nFrameLen;         //ch:输入数据大小 | en:input data size
        stConvertParam.enSrcPixelType = stImageInfo.enPixelType;    //ch:输入像素格式 | en:input pixel format
        stConvertParam.enDstPixelType = PixelType_Gvsp_BGR8_Packed; //ch:输出像素格式 | en:output pixel format  适用于OPENCV的图像格式
        //stConvertParam.enDstPixelType = PixelType_Gvsp_RGB8_Packed;   //ch:输出像素格式 | en:output pixel format
        stConvertParam.pDstBuffer = m_pBufForSaveImage;                    //ch:输出数据缓存 | en:output data buffer
        stConvertParam.nDstBufferSize = m_nBufSizeForSaveImage;            //ch:输出缓存大小 | en:output buffer size
        MV_CC_ConvertPixelType(m_hDevHandle, &stConvertParam);
        //RGB2BGR(pData,stImageInfo.nHeight, stImageInfo.nWidth);
        *getImage = cv::Mat(stImageInfo.nHeight, stImageInfo.nWidth, CV_8UC3, m_pBufForSaveImage);
    }
    (*getImage).copyTo(image);
    (*getImage).release();
    free(pData);
    return 0;
}

int HIKCamera::ReadBuffer(cv::Mat &image,unsigned char *pData, MV_FRAME_OUT_INFO_EX* stImageInfo)
{
    cv::Mat* getImage = new cv::Mat();
    m_nBufSizeForSaveImage = stImageInfo->nWidth * stImageInfo->nHeight * 3 + 2048;
    if (m_pBufForSaveImage)
    {
        free(m_pBufForSaveImage);
        m_pBufForSaveImage = nullptr;
    }
    m_pBufForSaveImage = (unsigned char*)malloc(m_nBufSizeForSaveImage);
    bool isMono;
    switch (stImageInfo->enPixelType)
    {
    case PixelType_Gvsp_Mono8:
    case PixelType_Gvsp_Mono10:
    case PixelType_Gvsp_Mono10_Packed:
    case PixelType_Gvsp_Mono12:
    case PixelType_Gvsp_Mono12_Packed:
        isMono = true;
        break;
    default:
        isMono = false;
        break;
    }
    if (isMono)
    {
        *getImage = cv::Mat(stImageInfo->nHeight, stImageInfo->nWidth, CV_8UC1, pData);
    }
    else
    {
        //转换图像格式为BGR8
        MV_CC_PIXEL_CONVERT_PARAM stConvertParam = { 0 };
        memset(&stConvertParam, 0, sizeof(MV_CC_PIXEL_CONVERT_PARAM));
        stConvertParam.nWidth = stImageInfo->nWidth;                 //ch:图像宽 | en:image width
        stConvertParam.nHeight = stImageInfo->nHeight;               //ch:图像高 | en:image height
        //stConvertParam.pSrcData = m_pBufForDriver;                  //ch:输入数据缓存 | en:input data buffer
        stConvertParam.pSrcData = pData;                  //ch:输入数据缓存 | en:input data buffer
        stConvertParam.nSrcDataLen = stImageInfo->nFrameLen;         //ch:输入数据大小 | en:input data size
        stConvertParam.enSrcPixelType = stImageInfo->enPixelType;    //ch:输入像素格式 | en:input pixel format
        stConvertParam.enDstPixelType = PixelType_Gvsp_BGR8_Packed; //ch:输出像素格式 | en:output pixel format  适用于OPENCV的图像格式
        //stConvertParam.enDstPixelType = PixelType_Gvsp_RGB8_Packed;   //ch:输出像素格式 | en:output pixel format
        stConvertParam.pDstBuffer = m_pBufForSaveImage;                    //ch:输出数据缓存 | en:output data buffer
        stConvertParam.nDstBufferSize = m_nBufSizeForSaveImage;            //ch:输出缓存大小 | en:output buffer size
        MV_CC_ConvertPixelType(m_hDevHandle, &stConvertParam);
        *getImage = cv::Mat(stImageInfo->nHeight, stImageInfo->nWidth, CV_8UC3, m_pBufForSaveImage);
    }
    (*getImage).copyTo(image);
    (*getImage).release();
    return 0;

}
void HIKCamera::RGB2BGR( unsigned char* pRgbData, unsigned int nWidth, unsigned int nHeight )
{
    if (!pRgbData )
    {
        return;
    }

    // red和blue数据互换
    for (unsigned int j = 0; j < nHeight; j++)
    {
        for (unsigned int i = 0; i < nWidth; i++)
        {
            unsigned char red = pRgbData[j * (nWidth * 3) + i * 3];
            pRgbData[j * (nWidth * 3) + i * 3]     = pRgbData[j * (nWidth * 3) + i * 3 + 2];
            pRgbData[j * (nWidth * 3) + i * 3 + 2] = red;
        }
    }
}

