#include "lab.h"

using namespace cv;
using namespace std;

void lab::lab5_1()
{
	string imageName = "..\\image\\gg.jpg";
	string imageName2 = "..\\image\\moon.jpg";

	Mat img = imread(imageName, IMREAD_COLOR);
	resize(img, img, Size(img.cols / 1.2, img.rows / 1.2));
	Mat img2 = imread(imageName2, IMREAD_COLOR);
	resize(img2, img2, Size(img.cols, img.rows));
	Mat converted;
	cvtColor(img, converted, COLOR_BGR2HSV);
	Mat green = converted.clone();
	inRange(converted, Scalar(30, 30, 30), Scalar(72, 255, 255), green);
	Mat dst, dst1, inverted;
	bitwise_not(green, inverted);
	bitwise_and(img, img, dst, inverted);
	bitwise_or(dst, img2, dst1, green);
	bitwise_or(dst, dst1, dst1);
	imshow("img", img);
	//imshow("green", green);
	//imshow("dst", dst);
	imshow("dst1", dst1);
	waitKey(0);
}