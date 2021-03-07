#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Mat sty;
Mat src = imread("/Users/eugene/eugene-lab/opencv/고양이.jpeg", IMREAD_COLOR); //파일 가져오gee

void on_level_change(int pos, void *userdata) {
    Mat blurred = *(Mat *) userdata;
    Mat edge;

    adaptiveThreshold(blurred, edge, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, (pos + 1) * 2 + 1,
                      1.5); //blockSize 트랙바로 조종 가능하게
    cvtColor(edge, edge, COLOR_GRAY2RGB);

    Mat dst;
    bitwise_and(sty, edge, dst);
    imshow("dst", dst);
}

void ptpColor() {


    if (src.empty()) {
        cout << "   img not found";
        return;
    }


    Mat blurred, gray;
    cvtColor(src, gray, COLOR_RGB2GRAY);   //gray image 생성
    //GaussianBlur(gray, blurred, Size(), 10);       //가우시안 블러
    medianBlur(gray, blurred, 5);             //메디안 블러

    Mat edge;
    adaptiveThreshold(blurred, edge, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 1.5); //엣지 검출, blockSize 트랙바로 조종
    cvtColor(edge, edge, COLOR_GRAY2RGB); //RGB 와 덧셈 가능하도록 RGB 로 변환
    //imshow("edge", edge);

    stylization(src, sty, 60, 0.5f);   //이미지 뭉개기
    //imshow("sty", sty);

    namedWindow("dst");
    //트랙바
    createTrackbar("track", "dst", 0, 20, on_level_change, (void *) &blurred);
    setTrackbarPos("track", "dst", 10);

    Mat dst;
    bitwise_and(sty, edge, dst);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}

int main()
{
    ptpColor();
}