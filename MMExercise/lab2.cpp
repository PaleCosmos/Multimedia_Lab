#include "lab.h"

using namespace cv;
using namespace std;

void lab::lab2_1() {
	string imageName = "..\\image\\temp.jpg";

	Mat image = imread(imageName.c_str(), IMREAD_COLOR);
	Mat new_image = Mat::zeros(image.size(), image.type());

	double alpha = 2.2;
	int beta = 50;

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			for (int k = 0; k < 3; k++) {
				new_image.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(alpha * (image.at<Vec3b>(i, j)[k]) + beta);
			}
		}
	}

	imshow("DW", image);

	imshow("DW2", new_image);

	waitKey(0);
};


void lab::lab2_2() {
	string imageName = "..\\image\\logo.png";
	string imageName2 = "..\\image\\coffee.jpg";

	Mat image1 = imread(imageName.c_str(), IMREAD_COLOR);
	Mat image2 = imread(imageName2.c_str(), IMREAD_COLOR);

	resize(image2, image2, cv::Size(image1.cols, image1.rows), 0, 0, INTER_NEAREST);

	Mat dst = Mat::zeros(image1.size(), image1.type());

	double alpha = 0.5;
	double beta = 1 - alpha;

	for (int y = 0; y < image1.rows; y++) {
		for (int x = 0; x < image1.cols; x++) {
			for (int c = 0; c < 3; c++) {
				dst.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha * image1.at<Vec3b>(y, x)[c] + beta * image2.at<Vec3b>(y, x)[c]);
			}
		}
	}

	imshow("DW2", dst);

	waitKey(0);
};
