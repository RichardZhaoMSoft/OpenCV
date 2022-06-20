#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp> 
#include <iostream>


//***************Otsu算法通过求类间方差极大值求自适应阈值******************
int otsu_threshold(const cv::Mat image, int low_gray, int high_gray) {
    if (image.channels() != 1) {
        std::cout << "Please input Gray-image!" << std::endl;
        return 0;
    }
    int threshold = 0; //Otsu算法阈值
    double var_Value = 0; //类间方差中间值保存
    double w_0 = 0, w_1 = 0; //前景像素点数所占比例
    double u_0 = 0, u_1 = 0; //前景平均灰度
    double histogram[256] = { 0 }; //灰度直方图，下标是灰度值，保存内容是灰度值对应的像素点总数
    uchar* data = image.data;
    double total_Num = image.rows * image.cols; //像素总数
    //计算灰度直方图分布，histogram数组下标是灰度值，保存内容是灰度值对应像素点数
    for (int i = 0; i < image.rows; i++) {   //为表述清晰，并没有把rows和cols单独提出来
        for (int j = 0; j < image.cols; j++) {
            histogram[data[i * image.step + j]]++;
        }
    }
    for (int i = low_gray; i < high_gray; i++) {
        //每次遍历之前初始化各变量
        w_1 = 0;		u_1 = 0;		w_0 = 0;		u_0 = 0;
        //***********背景各分量值计算**************************
        for (int j = low_gray; j <= i; j++) {//背景部分各值计算		
            w_1 += histogram[j];  //背景部分像素点总数
            u_1 += j * histogram[j]; //背景部分像素总灰度和
        }

        if (w_1 == 0) {//背景部分像素点数为0时退出
            continue;
        }
        u_1 = u_1 / w_1; //背景像素平均灰度
        w_1 = w_1 / total_Num; // 背景部分像素点数所占比例
        //***********背景各分量值计算**************************

        //***********前景各分量值计算**************************
        for (int k = i + 1; k < high_gray; k++) {
            w_0 += histogram[k];  //前景部分像素点总数
            u_0 += k * histogram[k]; //前景部分像素总灰度和
        }
        if (w_0 == 0) {//前景部分像素点数为0时退出
            break;
        }
        u_0 = u_0 / w_0; //前景像素平均灰度
        w_0 = w_0 / total_Num; // 前景部分像素点数所占比例
        //***********前景各分量值计算**************************

        //***********类间方差计算******************************
        double varValueI = w_0 * w_1 * (u_1 - u_0) * (u_1 - u_0); //当前类间方差计算

        if (var_Value < varValueI) {
            var_Value = varValueI;
            threshold = i;
        }
    }
    return threshold;
}