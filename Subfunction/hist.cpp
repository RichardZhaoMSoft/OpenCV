#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

cv::Mat hist(cv::Mat src, cv::OutputArray hist_img, cv::Size size) {
    int channels_hist[] = { 0 };
    const int size_hist[] = { 256 };
    float range_hist[] = { 0, 256 };
    const float* ranges[] = { range_hist };

    cv::Mat hist, mid_hist;
    cv::calcHist(&src, 1, channels_hist, cv::Mat(), hist, 1, size_hist, ranges, true, false);
    
    double max_hist = 0;
    if (size.width >= 3) {
        cv::GaussianBlur(hist, mid_hist, size, 0, 0);
        minMaxLoc(mid_hist, 0, &max_hist, 0, 0);
    }
    else {
        mid_hist = hist;
        minMaxLoc(hist, 0, &max_hist, 0, 0);
    }

    int rows = cvRound(max_hist);
    cv::Mat hist_image = cv::Mat::zeros(rows, 256, CV_8UC1);

    for (int i = 2; i < 254; i++) {
        int temp = (int)(mid_hist.at<float>(i, 0));
        if (temp) {
            hist_image.col(i).rowRange(cv::Range(rows - temp, rows)) = 255;
        }
    }
    cv::Mat resize_image;
    resize(hist_image, resize_image, cv::Size(256, 256));
    resize_image.copyTo(hist_img);
    return mid_hist;
}

//int main() {
//    cv::Mat src;
//    src = cv::imread("1028.png", 0);
//    //src = cv::imread(".\\source\\1378.png", 0);
//    if (!src.data) {
//        std::cout << "There is no picture" << std::endl;
//        return 0;
//    }
//    std::string str_file_dir, str_result_dir;
//    str_file_dir = "source";
//    str_result_dir = "result";
//
//    cv::Mat hist_src, hist_img;
//    hist_img = hist(src, hist_src, cv::Size(3, 3));
//    std::ostringstream hist_result;
//    hist_result << ".\\result\\x_nor\\" << "1" << ".png";
//    cv::imwrite(hist_result.str(), hist_src);
//}