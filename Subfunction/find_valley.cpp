#include <opencv2/opencv.hpp>
#include <json/json.h>
#include <string>
#include <iostream>

std::vector<int> find_valley(cv::Mat mid_hist) {
    std::vector<int> gray_valley(1);
    std::vector<int> gray_valley_val(3);
    int max_peak = 0, second_peak = 0;
    int max_peak_val = 0, second_peak_val = 0;

    for (int i = 4; i < 254; i++) {
        int temp_1 = (int)(mid_hist.at<float>(i - 2, 0));
        int temp_2 = (int)(mid_hist.at<float>(i - 1, 0));
        int temp_3 = (int)(mid_hist.at<float>(i, 0));
        int temp_4 = (int)(mid_hist.at<float>(i + 1, 0));
        int temp_5 = (int)(mid_hist.at<float>(i + 2, 0));

        if (temp_1 >= max_peak) {
            max_peak = temp_1;
            max_peak_val = i;
        }
        else if (temp_1 <= max_peak && temp_1 >= second_peak) {
            second_peak = temp_1;
            second_peak_val = i;
        }

        if (temp_1 == 0 && temp_2 == 0 && temp_3 != 0 && temp_4 != 0) {
            gray_valley.push_back(i);
            /*std::cout << "Çé¿ö1-i:" << i << std::endl;
            std::cout << "Çé¿ö1-temp_1:" << temp_1 << std::endl;
            std::cout << "Çé¿ö1-temp_2:" << temp_2 << std::endl;
            std::cout << "Çé¿ö1-temp_3:" << temp_3 << std::endl;
            std::cout << "Çé¿ö1-temp_4:" << temp_4 << std::endl;
            std::cout << "Çé¿ö1-temp_5:" << temp_5 << std::endl;*/
        }
        else if (temp_2 < temp_1 && temp_3 < temp_2 && temp_3 < temp_4 && temp_4 < temp_5) {
            gray_valley.push_back(i);
            /*std::cout << "Çé¿ö2-i:" << i << std::endl;
            std::cout << "Çé¿ö2-temp_1:" << temp_1 << std::endl;
            std::cout << "Çé¿ö2-temp_2:" << temp_2 << std::endl;
            std::cout << "Çé¿ö2-temp_3:" << temp_3 << std::endl;
            std::cout << "Çé¿ö2-temp_4:" << temp_4 << std::endl;
            std::cout << "Çé¿ö2-temp_5:" << temp_5 << std::endl;*/
        }
        else if (temp_4 == 0 && temp_5 == 0 && temp_3 != 0 && temp_2 != 0) {
            gray_valley.push_back(i);
            /*std::cout << "Çé¿ö3-i:" << i << std::endl;
            std::cout << "Çé¿ö3-temp_1:" << temp_1 << std::endl;
            std::cout << "Çé¿ö3-temp_2:" << temp_2 << std::endl;
            std::cout << "Çé¿ö3-temp_3:" << temp_3 << std::endl;
            std::cout << "Çé¿ö3-temp_4:" << temp_4 << std::endl;
            std::cout << "Çé¿ö3-temp_5:" << temp_5 << std::endl;*/
        }
    }

    std::cout << "max_peak_val:" << max_peak_val << std::endl;
    for (int i = 0; i < gray_valley.size(); i++) {
        std::cout << "gray_valley:" << gray_valley[i] << std::endl;
    }

    for (int i = 1; i < gray_valley.size(); i++) {
        if (gray_valley[i - 1] <= max_peak_val && max_peak_val <= gray_valley[i]) {
            gray_valley_val[1] = gray_valley[i - 1];
            gray_valley_val[2] = gray_valley[i];
            break;
        }
    }
    gray_valley_val[0] = max_peak_val;
    return gray_valley_val;
}
