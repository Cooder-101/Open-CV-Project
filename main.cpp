#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat rotateimg(Mat src,int angle){
    Point2f center((src.cols-1)/2.0, (src.rows-1)/2.0);
    Mat rot = getRotationMatrix2D(center, angle, 1.0);
    Rect2f box = RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
    rot.at<double>(0,2) += box.width/2.0 - src.cols/2.0;
    rot.at<double>(1,2) += box.height/2.0 - src.rows/2.0;
    Mat final_img;
    warpAffine(src, final_img, rot, box.size());
    return final_img;
}

int main() {
    cout<<"Enter Image File Path : ";
    string imgpath;
    getline(cin,imgpath);
    Mat src = imread(imgpath,IMREAD_UNCHANGED);
    if(src.empty()){
        cout<<"ERROR Loading Image File."<<endl;
        return -1;
    }
    cout<<"Enter Angle : ";
    int angle;
    cin>>angle;
    angle = angle%360;
    Mat rotatedimg = rotateimg(src,angle);
    if(rotatedimg.empty()){
        cout<<"ERROR Rotating Image."<<endl;
        return -1;
    }
    imshow("Original Image", src);
    imshow("Rotated Image", rotatedimg);
    waitKey(0);
    return 0;
}