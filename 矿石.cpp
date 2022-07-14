#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


Mat img;
int main(){
    VideoCapture cap(0);
    Mat img;
    while(true){

        cap.read(img);
        Mat mask;
        cvtColor(img,mask,COLOR_BGR2HSV);//转换
        inRange(mask, Scalar(18, 50, 103), Scalar(60,255, 255),mask);//二值化
        //imshow("mask", mask);
        //waitKey(1);
        Mat imgBlur;
        GaussianBlur(mask, imgBlur, Size(11, 11), 2, 2);//高斯模糊
        Mat imgBright;
        threshold(imgBlur, imgBright, 127, 255, THRESH_BINARY);//再次二值化
        //imshow("mask2", imgBright);
        //waitKey(1);
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//内核
        morphologyEx(imgBright,mask, MORPH_CLOSE, kernel);//闭运算
        //imshow("mask3", mask);
        //waitKey(1);

        Mat element, imgEro, imgDil,imgCanny;
            element = getStructuringElement(MORPH_RECT, Size(6, 6));
            erode(mask, imgEro, element, Point(-1, -1), 5);//先侵蚀
            imshow("mask4", imgEro);
            waitKey(1);
            //Canny(mask, imgCanny, 25, 75);
            //dilate(imgEro, imgDil, element, Point(-1, -1), 5);//膨胀
            //imshow("mask5", imgDil);
            //waitKey(1);



        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;


        findContours(imgEro.clone(), contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_SIMPLE);//找出子轮廓与父轮廓
        for (int i = 0; i < contours.size(); i++)
        {
          Rect rect = boundingRect(contours[i]);
            float wide=rect.width;
            float high=rect.height;

            float area = contourArea(contours[i]);//contourArea轮廓内的区域大小
            //cout << area << endl;//输出语句
            if (area >2000.00) //过滤图形
            {
                rectangle(img, rect, Scalar(0, 0, 255), 1);
                drawContours(img, contours,i, Scalar(255,0,255),2);
            }
            if(high/wide>1.5){
                cout<<"txm"<<endl;
            }
            else if(high/wide>1.1&&high/wide<1.5){
                cout<<"R"<<endl;
            }
            else if(contours.size()==1){
                cout<<"kongbai"<<endl;
            }
      }
        imshow("Image",img);

        waitKey(1);

    }
}









