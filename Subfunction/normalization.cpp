#include <opencv2/opencv.hpp>
#include <json/json.h>
#include <string>
#include <iostream>

cv::Mat NormalizeImage(cv::Mat img){
    int height = img.rows;
    int width = img.cols;
    int red_Value, green_Value, blue_Value;
    double sum_pixel, epslon = 0.000001;

    cv::Mat nor_img(height, width, 0);

    for (int i = 0; i < height; i++) {
        for (int j = 500; j < 1500; j++) {
            cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
            red_Value = pixel.val[0];
            green_Value = pixel.val[1];
            blue_Value = pixel.val[2];
            
            // 加上epslon，为了防止除以0的情况发生
            sum_pixel = red_Value + green_Value + blue_Value + epslon;
            red_Value = red_Value / sum_pixel * 255.0;
            blue_Value = blue_Value / sum_pixel * 255.0;
            green_Value = green_Value / sum_pixel * 255.0;
            //0.299 * R(i,j) + 0.587 * G(i,j) + 0.114 * B(i,j)
            nor_img.at<uchar>(i, j) = (int)(0.299 * red_Value + 0.587 * green_Value + 0.114 * blue_Value);

        }
    }
    //4、返回归一化后的图像；
    return nor_img;
}

//int main() {
//	cv::Mat src;
//	src = cv::imread("1028.png");
//	//src = cv::imread(".\\source\\1378.png", 0);
//	if (!src.data) {
//		std::cout << "There is no picture" << std::endl;
//		return 0;
//	}
//	std::string str_file_dir, str_result_dir;
//	str_file_dir = "source";
//	str_result_dir = "result";
//	cv::Mat nor_src;
//	////nor_src = NormalizeImage(src);
//	//cv::normalize(src, src, 0, 255, cv::NORM_L2);
//	//
//	//int height = src.rows;
//	//int width = src.cols;
//	///*std::cout << "width:" << width  << std::endl;
//	//std::cout << "height:" << height << std::endl;*/
//	//for (int i = 0; i < height; i++) {
//	//	for (int j = 0; j < width; j++) {
//	//		nor_src.at<uchar>(i, j) = src.at<uchar>(i, j) * 255;
//	//		/*std::cout << "i:" << i << std::endl;
//	//		std::cout << "j:" << j << std::endl;*/
//	//	}
//	//}
//
//  nor_src = NormalizeImage(src);
//	std::ostringstream nor_src_result;
//	nor_src_result << ".\\" << str_result_dir << "\\x_nor\\" << "1" << ".png";
//	cv::imwrite(nor_src_result.str(), nor_src);
//	return 0;
//}
