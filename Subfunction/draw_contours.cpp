#include "aidi_vision.h"
#include <opencv2/opencv.hpp>
#include <json/json.h>
#include <string>
#include <iostream>

typedef std::vector<cv::Point> CONTOUR;
typedef std::vector<CONTOUR> CONTOURS;
/** @绘制CONTOURS.

这个函数可以将CONTOURS里的数据绘制在输入的图片上。

原图像是任意的，三通道的原图上可以绘制出任意颜色的线条，但灰度图上只能绘制出黑白灰三种颜色的线条。

@CONTOURS的形式为std::vector<std::vector<cv::Point>>，里面包含了一系列点，与opencv的形式相同。

@area_min是面积的最小值，
    如果该值不为0
        绘制曲线，
        @曲线
    否则
        通过contourArea函数绘制矩形框
        @矩形框有四个属性：x, y, width, height,分别代表左上角点的坐标和长宽。
 */
//画contours
int draw_contours(cv::Mat src, cv::OutputArray img, CONTOURS contours, int area_min) {
    if (area_min == 0) {
        for (size_t i = 0; i < contours.size(); i++) {
            for (size_t j = 1; j < contours[i].size(); j++) {               
                cv::line(src, contours[i][j], contours[i][j - 1], cv::Scalar(0, 255, 255), 3);
            }
        }
    }
    else {
        for (int i = 0; i < contours.size(); i++) {
            double area = cv::contourArea(contours[i]);
            if (area > area_min) {
                cv::Rect boundRect = cv::boundingRect(contours[i]);
                int x_0 = boundRect.x;
                int y_0 = boundRect.y;
                int w_0 = boundRect.width;
                int h_0 = boundRect.height;
                cv::rectangle(src, cv::Point(x_0, y_0), cv::Point(x_0 + w_0, y_0 + h_0), cv::Scalar(255, 255, 255), 2, 8);
            }
        }
    }
    src.copyTo(img);
    return 0;
}