#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Mat sty;
Mat src = imread("/Users/eugene/eugene-lab/opencv_project/lenna.png", IMREAD_COLOR);

void ptpGray() {
    Mat gray, dst, noise;

    cvtColor(src, gray, COLOR_BGR2GRAY);  //그래이로 바꿔줌
    gray +=50;
    Mat grayClone = gray.clone();              //클론생성
    gray = ~gray;//색반전

    //----------------------노이즈 생성-------------------------//
    Mat noize(gray.size(), CV_32SC1);
    randn(noize, 0, 50);
    add(gray, noize, gray, Mat(), gray.type());

    //------------------------모션블러--------------------------//
    Mat mask = Mat::zeros(15, 15, CV_32FC1);
    mask(Range(6, 7), Range(0, 15)) = Mat::ones(Size(mask.cols, 1), CV_32FC1);
    mask = mask / 15;
    Mat motion;
    filter2D(gray, motion, -1, mask);
    filter2D(motion, motion, -1, mask);
    motion.convertTo(gray, CV_8U);
    imshow("motion", gray);
    //-------------------------최종 이미지-------------------------//
    add(gray, grayClone, gray);

    //-------------------------이미지 출력-------------------------//
    imshow("gray", gray);
    waitKey();
    destroyAllWindows();


}

int main() {
    ptpGray();
}
