#pragma once

#ifndef SEGMENTATION_H
#define SEGMENTATION_H
cv::Mat valley_segmentation(cv::Mat src, std::vector<int> valley);
cv::Mat segmentation(cv::Mat src, int low_gray, int high_gray);
#endif#
