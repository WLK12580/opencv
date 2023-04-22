#include<iostream>
#include<opencv4/opencv2/opencv.hpp>
int main(){
    cv::Mat img;
    img=cv::imread("../OIP-C.jpg");
    if(!img.data){
        std::cout<<"imread failed"<<std::endl;
        return -1;
    }else{
        cv::imshow("img",img);
        cv::waitKey();
    }
    return 0;
}