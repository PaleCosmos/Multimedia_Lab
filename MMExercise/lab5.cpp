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

	cvtColor(img, img, COLOR_BGR2YCrCb);
	cvtColor(img2, img2, COLOR_BGR2YCrCb);

	Vec3b t;

	int g = img.rows >> 4;
	int v = img.cols >> 3;

	for (int y = g; y < img.rows; y++) {
		for (int x = v; x < img.cols - v; x++) {
			t = img.at<Vec3b>(y, x);

			if (t[1] >= 100 || t[2] >= 110) {
				img2.at<Vec3b>(y, x) = img.at<Vec3b>(y, x);
			}
		}
	}

	cvtColor(img2, img2, COLOR_YCrCb2BGR);

	imshow("img", img2);

	waitKey(0);
}