#include "lab.h"

using namespace cv;
using namespace std;

void lab::lab4_1()
{
	string imageName = "..\\image\\Lena.png";

	Mat src = imread(imageName.c_str(), IMREAD_COLOR);
	Mat dst1, dst2;

	double alpha = 0.7;
	double beta = 0.0;

	cin >> alpha;

	cvtColor(src, dst1, COLOR_BGR2HSV);
	cvtColor(src, dst2, COLOR_BGR2YCrCb);

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			dst1.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(alpha * (dst1.at<Vec3b>(y, x)[2] + beta));
			dst2.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(alpha * (dst2.at<Vec3b>(y, x)[0] + beta));
		}
	}

	cvtColor(dst1, dst1, COLOR_HSV2BGR);
	cvtColor(dst2, dst2, COLOR_YCrCb2BGR);

	imshow("origin", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey(0);
}