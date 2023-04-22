#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/calib3d/calib3d.hpp>
#include<vector>
#include<fstream>

using namespace std;
using namespace cv;

#define IMG_NUM 6;

int main()
{
    //所读图像文件夹的路经
    cv::String IMG_PATH="../Calibration_IMG";
    //设置保存所读文件的路经
    std::vector<cv::String> Img_Path ;

    //读取指定路径下的文件到 容器中
    cv::glob(IMG_PATH,Img_Path);
    
    //标定版中每行、没列的角点数
    Size broad_size= Size(9,6);
    //存储每张标定版的角点
    std::vector<Point2f> img_cores_buf;
    //存储所有的角点
    std::vector<std::vector<cv::Point2f>> img_core_vec;

    Size img_size;

    //显示测试
    for(int i=0;i<Img_Path.size();i++)
    {
        std::cout<<"IMG_PATH_OUT:"<<Img_Path[i]<<std::endl;
        cv::Mat Img_data=cv::imread(Img_Path[i]);
        // cv::imshow("IMG_SHOW",Img_data);
        if(!findChessboardCorners(Img_data,broad_size,img_cores_buf))
        {
            std::cout<<"cannot find chessboard corners"<<std::endl;
            continue;
        }
        else
        {
            cv::Mat img_gray;
            cv::cvtColor(Img_data,img_gray,cv::COLOR_RGB2GRAY);
            cv:;find4QuadCornerSubpix(img_gray,img_cores_buf,Size(5,5));
            drawChessboardCorners(img_gray,broad_size,img_cores_buf,true);
            img_core_vec.push_back(img_cores_buf);
            // cv::imshow("cali_img",img_gray);
            string save_img_path="./ret_img/"+to_string(i)+".jpg";
            cv::imwrite(save_img_path,img_gray);
            // cv::waitKey(500);  
        }
        img_size.width=Img_data.cols;
        img_size.height=Img_data.rows;
        Img_data.release();
        cout<<"test2:"<<img_size.width<<" "<<img_size.height<<endl;
    }

    //相机标定
    //保存标定板上角点的三维坐标
    vector<vector<Point3f>> object_points;
    //标定板上实际棋盘格的大小
    Size cores_size=Size(10,10);
    for(int i=0;i<Img_Path.size();i++)
    {
        vector<Point3f> temp;
        for(int j=0;j<broad_size.height;j++)
        {
            for (int t=0;t<broad_size.width;t++)
            {
                Point3f real_point;
                real_point.x=j*cores_size.width;
                real_point.y=t*cores_size.height;
                real_point.z=0;
                // cout<<"real_point:"<<real_point.x<<" "<<real_point.y<<" "<<real_point.z<<endl;
                temp.push_back(real_point);
            }
        }
        object_points.push_back(temp);
    }
    //相机的内外参数
    cv::Mat cameraMatix=Mat(3,3,CV_32FC1,Scalar::all(0));//相机内参矩阵

    vector<int> point_core_num;//每幅图像中的角点数

    Mat discoeffs=Mat(1,5,CV_32FC1,Scalar::all(0));//相机的5个畸变参数

    vector<Mat> rotal_vec;//每幅图像的旋转向量

    vector<Mat> trans_vec;//每幅图像的平移向量

    //相机标定
    calibrateCamera(object_points,img_core_vec,img_size,cameraMatix,discoeffs,rotal_vec,trans_vec,0);
    //利用标定的结果矫正图像

    for(int k=0;k<Img_Path.size();k++)
    {
        Mat read_img=cv::imread(Img_Path[k]);
        Mat new_img=read_img.clone();
        cv::undistort(read_img,new_img,cameraMatix,discoeffs);
        // imshow("source",read_img);
        // imshow("ret",new_img);

        waitKey(500);
        read_img.release();
        new_img.release();
    }
    std::ofstream fout("Out.txt",ios::in);
    fout<<"相机内参矩阵："<<endl;
    fout<<cameraMatix<<endl;
    fout<<"畸变系数："<<endl;
    fout<<discoeffs<<endl;
    fout.close();
    cout<<cameraMatix<<endl<<"ret="<<cameraMatix.at<float>(0,1)<<endl;

    //图像去畸变
    //图像去畸变

    std::string Tunnel_img = "../Tunnel_IMG";
    std::vector<cv::String> Tunnel_Path;
    cv::glob(Tunnel_img, Tunnel_Path);

    for (size_t i = 0; i < Tunnel_Path.size(); i++)
    {
        cv::Mat Source_IMG = cv::imread(Tunnel_Path[i]);
        cv::Size reszie_img = cv::Size(4000, 3000);
        cv::Mat dest_img;
        cv::resize(Source_IMG, dest_img, reszie_img, 0, 0, INTER_AREA);
        cv::Mat New_IMG = dest_img.clone();
        cv::undistort(dest_img, New_IMG, cameraMatix, discoeffs);
        cv::imshow("Sour_IMG", dest_img);
        cv::imshow("Dst_IMG", New_IMG);
        std::string ret_img = "../Ret_IMG/" + to_string(i) + ".jpg";
        cv::imwrite(ret_img, New_IMG);
        cv::waitKey(500);
        Source_IMG.release();
        New_IMG.release();
    }



    return 0;
}