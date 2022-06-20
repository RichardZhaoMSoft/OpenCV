#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp> 
#include <iostream>


//***************Otsu�㷨ͨ������䷽���ֵ������Ӧ��ֵ******************
int otsu_threshold(const cv::Mat image, int low_gray, int high_gray) {
    if (image.channels() != 1) {
        std::cout << "Please input Gray-image!" << std::endl;
        return 0;
    }
    int threshold = 0; //Otsu�㷨��ֵ
    double var_Value = 0; //��䷽���м�ֵ����
    double w_0 = 0, w_1 = 0; //ǰ�����ص�����ռ����
    double u_0 = 0, u_1 = 0; //ǰ��ƽ���Ҷ�
    double histogram[256] = { 0 }; //�Ҷ�ֱ��ͼ���±��ǻҶ�ֵ�����������ǻҶ�ֵ��Ӧ�����ص�����
    uchar* data = image.data;
    double total_Num = image.rows * image.cols; //��������
    //����Ҷ�ֱ��ͼ�ֲ���histogram�����±��ǻҶ�ֵ�����������ǻҶ�ֵ��Ӧ���ص���
    for (int i = 0; i < image.rows; i++) {   //Ϊ������������û�а�rows��cols���������
        for (int j = 0; j < image.cols; j++) {
            histogram[data[i * image.step + j]]++;
        }
    }
    for (int i = low_gray; i < high_gray; i++) {
        //ÿ�α���֮ǰ��ʼ��������
        w_1 = 0;		u_1 = 0;		w_0 = 0;		u_0 = 0;
        //***********����������ֵ����**************************
        for (int j = low_gray; j <= i; j++) {//�������ָ�ֵ����		
            w_1 += histogram[j];  //�����������ص�����
            u_1 += j * histogram[j]; //�������������ܻҶȺ�
        }

        if (w_1 == 0) {//�����������ص���Ϊ0ʱ�˳�
            continue;
        }
        u_1 = u_1 / w_1; //��������ƽ���Ҷ�
        w_1 = w_1 / total_Num; // �����������ص�����ռ����
        //***********����������ֵ����**************************

        //***********ǰ��������ֵ����**************************
        for (int k = i + 1; k < high_gray; k++) {
            w_0 += histogram[k];  //ǰ���������ص�����
            u_0 += k * histogram[k]; //ǰ�����������ܻҶȺ�
        }
        if (w_0 == 0) {//ǰ���������ص���Ϊ0ʱ�˳�
            break;
        }
        u_0 = u_0 / w_0; //ǰ������ƽ���Ҷ�
        w_0 = w_0 / total_Num; // ǰ���������ص�����ռ����
        //***********ǰ��������ֵ����**************************

        //***********��䷽�����******************************
        double varValueI = w_0 * w_1 * (u_1 - u_0) * (u_1 - u_0); //��ǰ��䷽�����

        if (var_Value < varValueI) {
            var_Value = varValueI;
            threshold = i;
        }
    }
    return threshold;
}