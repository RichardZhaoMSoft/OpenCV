#pragma once
#ifndef DRAW_CONTOURS_H
#define DRAW_CONTOURS_H

typedef std::vector<cv::Point> CONTOUR;
typedef std::vector<CONTOUR> CONTOURS;

int draw_contours(cv::Mat src, cv::OutputArray img, CONTOURS contours, int area_min);
#endif#