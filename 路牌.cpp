#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


Mat img;
/*
void object(Mat img){
     Mat mask;
     cvtColor(img,mask,COLOR_BGR2HSV);//转换
     inRange(mask, Scalar(100, 150, 150), Scalar(124,255, 255),mask);//二值化
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
     imshow("mask3", mask);
     waitKey(1);

     Mat element, imgEro, imgDil,imgCanny;
         element = getStructuringElement(MORPH_RECT, Size(5, 5));
         erode(mask, imgEro, element, Point(-1, -1), 3);//先侵蚀
         //imshow("mask4", imgEro);
         //waitKey(1);
         //Canny(mask, imgCanny, 25, 75);
         dilate(imgEro, imgDil, element, Point(-1, -1), 5);//膨胀
         //imshow("mask5", imgDil);
         //waitKey(1);
     vector<vector<Point>> contours;
     vector<Vec4i> hierarchy;

     findContours(imgDil.clone(), contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_SIMPLE);//找出子轮廓与父轮廓
     for (int i = 0; i < contours.size(); i++)
     {
         //vector<vector<Point>> conPoly(contours.size());
         //vector<Rect> boundRect(contours.size());
         vector<RotatedRect>box(contours.size());//定义点的集合
         Point2f rect[4];//定义数组
         box[i]=minAreaRect(Mat(contours[i]));//得到最小外接矩形的四个点
         //circle(img,Point(box[i].center.x,box[i].center.y),5,Scalar(255,255,255),-1,8);外接矩形的中心点
         box[i].points(rect);//将点放入rect中

         float area = contourArea(contours[i]);//contourArea轮廓内的区域大小
         //cout << area << endl;//输出语句


         if (area > 4000.00) //过滤图形
         {
             for(int j=0;j<4;j++){
                 line(img,rect[j],rect[(j+1)%4],Scalar(0,0,255),2,8);//画出最小外接矩形
             }

             //double peri = arcLength(contours[i], true);
             //approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
             //boundRect[i] = boundingRect(conPoly[i]);
             drawContours(img, contours,i, Scalar(255,0 , 255),2);
             //rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(0,255,0),5);
         }

     }

}


*/
int main(){
    VideoCapture cap(0);
    Mat img;
    while(true){

        cap.read(img);
        Mat mask;
        cvtColor(img,mask,COLOR_BGR2HSV);//转换
        inRange(mask, Scalar(100, 150, 150), Scalar(124,255, 255),mask);//二值化
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
        imshow("mask3", mask);
        waitKey(1);

        Mat element, imgEro, imgDil,imgCanny;
            element = getStructuringElement(MORPH_RECT, Size(5, 5));
            erode(mask, imgEro, element, Point(-1, -1), 3);//先侵蚀
            //imshow("mask4", imgEro);
            //waitKey(1);
            //Canny(mask, imgCanny, 25, 75);
            dilate(imgEro, imgDil, element, Point(-1, -1), 5);//膨胀
            //imshow("mask5", imgDil);
            //waitKey(1);
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;

        findContours(imgDil.clone(), contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_SIMPLE);//找出子轮廓与父轮廓
        for (int i = 0; i < contours.size(); i++)
        {
            //vector<vector<Point>> conPoly(contours.size());
            //vector<Rect> boundRect(contours.size());
            /*
            vector<RotatedRect>box(contours.size());//定义点的集合
            Point2f rect[4];//定义数组
            box[i]=minAreaRect(Mat(contours[i]));//得到最小外接矩形的四个点
            box[i].points(rect);//将点放入rect中
            */
            RotatedRect rect=minAreaRect(contours[i]);
                    Point2f P[4];
                    rect.points(P);//返回矩形的四个顶点
            double angle=rect.angle;
            float area = contourArea(contours[i]);//contourArea轮廓内的区域大小
            //cout << area << endl;//输出语句
            if (area > 4000.00) //过滤图形
            {
                for(int j=0;j<=3;j++)
                {
                    line(img,P[j],P[(j+1)%4],Scalar(0,0,255),2,8);
                }
                /*
                for(int j=0;j<1;j++){
                    line(img,rect[j],rect[(j+1)%4],Scalar(0,0,255),2,8);//画出最小外接矩形
                }
                */
                //double peri = arcLength(contours[i], true);
                //approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
                //boundRect[i] = boundingRect(conPoly[i]);
                drawContours(img, contours,i, Scalar(255,0 , 255),2);
                //rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(0,255,0),5);
          }
            cout<<angle<<endl;
            if(angle>-60&&angle<-40){
                cout<<angle<<endl;
                cout<<"右转"<<endl;
}
            else if(angle>-40&&angle<0){
                cout<<"左转"<<endl;
            }
            else if(angle=0){
                cout<<"直行"<<endl;
            }

        }
        //object(img);
        imshow("Image",img);
        waitKey(1);

    }

}


}

