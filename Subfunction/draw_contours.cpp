#include "aidi_vision.h"
#include <opencv2/opencv.hpp>
#include <json/json.h>
#include <string>
#include <iostream>

typedef std::vector<cv::Point> CONTOUR;
typedef std::vector<CONTOUR> CONTOURS;
/** @����CONTOURS.

����������Խ�CONTOURS������ݻ����������ͼƬ�ϡ�

ԭͼ��������ģ���ͨ����ԭͼ�Ͽ��Ի��Ƴ�������ɫ�����������Ҷ�ͼ��ֻ�ܻ��Ƴ��ڰ׻�������ɫ��������

@CONTOURS����ʽΪstd::vector<std::vector<cv::Point>>�����������һϵ�е㣬��opencv����ʽ��ͬ��

@area_min���������Сֵ��
    �����ֵ��Ϊ0
        �������ߣ�
        @����
    ����
        ͨ��contourArea�������ƾ��ο�
        @���ο����ĸ����ԣ�x, y, width, height,�ֱ�������Ͻǵ������ͳ���
 */
//��contours
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