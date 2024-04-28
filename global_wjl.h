#ifndef GLOBAL_WJL_H
#define GLOBAL_WJL_H
#include "user.h"
#include <opencv2/opencv.hpp>
#include <QImage>
extern User currentUser;
class Global_WJL
{
public:
    Global_WJL() {}
    QImage cvMat2QImage(const cv::Mat& mat);
};
#endif // GLOBAL_WJL_H
