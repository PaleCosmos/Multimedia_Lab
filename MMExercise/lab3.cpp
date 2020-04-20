#include "lab.h"

using namespace cv;
using namespace std;

void lab::lab3_1_1() {
	string imageName = "..\\image\\logo.png";

	Mat src = imread(imageName.c_str(), IMREAD_COLOR);
	Mat dst;

	cvtColor(src, src, COLOR_BGR2GRAY);

	equalizeHist(src, dst);

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
}

void lab::lab3_1_2() {
	string imageName = "..\\image\\logo.png";

	Mat image = imread(imageName.c_str(), IMREAD_GRAYSCALE);

	Mat hist;
	int histSize = 256;
	float range[] = { 0,256 };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;

	calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
		line(histImage, Point(bin_w * (i - 1), hist_h -
			cvRound(hist.at<float>(i - 1))), Point(bin_w * (i), hist_h -
				cvRound(hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);

	imshow("dem", histImage);

	waitKey(0);
}

void lab::lab3_2() {
	string imageName = "..\\image\\lena_noise.png";

	Mat image = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	Mat newImage = Mat::zeros(image.size(), image.type());

	int square = 3;
	int half = square / 2;

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			int sum = 0;
			int g = 0;

			for (int v = y - half; v <= y + half; v++) {
				if (v >= 0 && v < image.rows)
					for (int l = x - half; l <= x + half; l++) {
						if (l >= 0 && l < image.cols) {
							sum += image.at<uchar>(v, l);
							g++;
						}
					}
			}

			if (g > 0)
				newImage.at<uchar>(y, x) = sum / g;
		}
	}

	imshow("x", newImage);

	waitKey(0);
}

void lab::lab3_3() {
	string imageName = "..\\image\\lena_noise.png";

	Mat image = imread(imageName.c_str(), IMREAD_COLOR);
	Mat newImage = Mat::zeros(image.size(), image.type());

	int square = 5;
	int half = square / 2;

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			int sum[3] = { 0,0,0 };
			int g = 0;
			for (int c = 0; c < 3; c++) {
				for (int v = y - half; v <= y + half; v++) {
					if (v >= 0 && v < image.rows)
						for (int l = x - half; l <= x + half; l++) {
							if (l >= 0 && l < image.cols) {
								sum[c] += image.at<Vec3b>(v, l)[c];
								if (c == 0)
									g++;
							}
						}
				}

				if (g > 0)
					newImage.at<Vec3b>(y, x)[c] = sum[c] / g;
			}
		}
	}

	imshow("x", newImage);

	waitKey(0);
}