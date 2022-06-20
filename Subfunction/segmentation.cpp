#include <opencv2/opencv.hpp>
#include <json/json.h>
#include <string>
#include <iostream>

cv::Mat valley_segmentation(cv::Mat src, std::vector<int> valley) {
    int height = src.rows;
    int width = src.cols;
    
    cv::Mat gary_src(height, width, 0);
    int start_gray, end_gray = 0;
    if (valley[0] >= 75) {
        if (valley[2] >= 70) {
            start_gray = 54;
            end_gray = 70;
        }
        else {
            start_gray = 60;
            end_gray = valley[2];
        }
    }
    else {
        start_gray = 40;
        end_gray = 48;
    }
    //生成一张新的roi_gary图用来处理
    for (int i = 0; i < height; i++) {
        for (int j = 500; j < 1500; j++) {
            int gray_value = src.at<uchar>(i, j);
            //if (start_gray <= gray_value and gray_value < end_gray)
            if (start_gray <= gray_value and gray_value < end_gray) {
                gary_src.at<uchar>(i, j) = 255;
            }
        }
    }
    return gary_src;
}

cv::Mat segmentation(cv::Mat src, int low_gray, int high_gray) {
    int height = src.rows;
    int width = src.cols;
    cv::Mat gary_src(height, width, 0);
    for (int i = 0; i < height; i++) {
        for (int j = 500; j < 1500; j++) {
            int src_value = src.at<uchar>(i, j);
            if (src_value >= high_gray || src_value <= low_gray) {
                gary_src.at<uchar>(i, j) = 0;
            }
            else {
                gary_src.at<uchar>(i, j) = src_value;
            }
        }
    }
    return gary_src;
}
