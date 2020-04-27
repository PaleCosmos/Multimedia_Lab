#include "lab.h"
#ifndef SQUARE
#define SQUARE 5
#endif

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

// Average Filter Gray
void lab::lab3_2_1() {
	string imageName = "..\\image\\lena_noise.png";

	Mat image = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	Mat newImage = Mat::zeros(image.size(), image.type());

	int square = SQUARE;
	int half = square / 2;
	int sum, g;

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			sum = 0;
			g = 0;

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

	imshow("Average Filter Gray", newImage);

	waitKey(0);
}

// Gaussian Filter Gray
void lab::lab3_2_2() {
	string imageName = "..\\image\\lena_noise.png";

	Mat image = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	Mat newImage = Mat::zeros(image.size(), image.type());

	int mask = SQUARE;
	int half = mask / 2;
	double sum, weight, g;

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			sum = 0;
			weight = 0;
			g = 0;

			for (int v = y - half; v <= y + half; v++) {
				if (v >= 0 && v < image.rows)
					for (int l = x - half; l <= x + half; l++) {
						if (l >= 0 && l < image.cols) {
							weight = pow(2, -1 * (abs(y - v) + abs(x - l)));
							sum += weight * image.at<uchar>(v, l);
							g += weight;
						}
					}
			}

			if (g > 0)
				newImage.at<uchar>(y, x) = (int)sum / g;
		}
	}

	imshow("Gaussian Filter Gray", newImage);

	waitKey(0);
}

// Average Filter Color
void lab::lab3_3_1() {
	string imageName = "..\\image\\lena_noise.png";

	Mat image = imread(imageName.c_str(), IMREAD_COLOR);
	Mat newImage = Mat::zeros(image.size(), image.type());

	int square = SQUARE;
	int half = square / 2;
	int g;

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			int sum[3] = { 0,0,0 };
			g = 0;
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

	imshow("Average Filter Color", newImage);

	// 비교용
	//waitKey(0);
}

// Gaussian Filter Color
void lab::lab3_3_2() {
	string imageName = "..\\image\\lena_noise.png";

	Mat image = imread(imageName.c_str(), IMREAD_COLOR);
	Mat newImage = Mat::zeros(image.size(), image.type());

	int square = SQUARE;
	int half = square / 2;
	double g, weight;

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			double sum[3] = { 0,0,0 };
			g = 0;
			weight = 0;
			for (int c = 0; c < 3; c++) {
				for (int v = y - half; v <= y + half; v++) {
					if (v >= 0 && v < image.rows)
						for (int l = x - half; l <= x + half; l++) {
							if (l >= 0 && l < image.cols) {
								weight = pow(2, -1 * (abs(y - v) + abs(x - l)));
								sum[c] += weight * image.at<Vec3b>(v, l)[c];
								if (c == 0)
									g += weight;
							}
						}
				}

				if (g > 0)
					newImage.at<Vec3b>(y, x)[c] = sum[c] / g;
			}
		}
	}

	imshow("Gaussian Filter Color", newImage);

	waitKey(0);
}

// Median Filter Color
void lab::lab3_3_3() {
	string imageName = "..\\image\\lena_noise.png";

	Mat image = imread(imageName.c_str(), IMREAD_COLOR);
	Mat newImage = Mat::zeros(image.size(), image.type());

	int square = SQUARE;
	int half = square / 2;
	int pow = square * square;
	int temp, c;
	int** arr = new int* [3];

	for (c = 0; c < 3; c++) {
		arr[c] = new int[pow];
		fill_n(arr[c], pow, 0);
	}

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			for (temp = 0, c = 0; c < 3; temp = 0, c++) {
				for (int v = y - half; v <= y + half; v++) {
					if (v >= 0 && v < image.rows)
						for (int l = x - half; l <= x + half; l++) {
							if (l >= 0 && l < image.cols) {
								arr[c][temp] = image.at<Vec3b>(v, l)[c];
							}
							temp++;
						}
				}

				sort(arr[c], arr[c] + pow);
				newImage.at<Vec3b>(y, x)[c] = arr[c][pow / 2];
				fill_n(arr[c], pow, 0);
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		delete[] arr[i];
	}

	delete[] arr;

	imshow("Median Filter Color", newImage);

	// 비교용
	waitKey(0);
}

// Derivative Filter
void lab::lab3_4() {
	string imageName = "..\\image\\Lena.png";
	int ksize = 3;
	int half = ksize >> 1;
	float temp0, temp1, temp2;

	Mat image = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	Mat Gmagnotude = Mat::zeros(image.size(), CV_8U);

	float kernelx[3][3] = { {-1, 0, 1}, {-2, 0, 2},{-1, 0, 1} };
	float kernely[3][3] = { {-1, -2, -1}, {0, 0, 0},{1, 2, 1} };

	for (int y = half; y < image.rows - half; y++) {
		for (int x = half; x < image.cols - half; x++) {
			temp0 = temp1 = temp2 = 0;
			for (int i = 0; i < ksize; i++) {
				for (int j = 0; j < ksize; j++) {
					temp0 = image.at<uchar>(y + (i - half), x + (j - half));
					temp1 += temp0 * kernelx[i][j];
					temp2 += temp0 * kernely[i][j];

					Gmagnotude.at<uchar>(y, x) = sqrt(temp1 * temp1 + temp2 * temp2);
				}
			}
		}
	}

	imshow("Derivative Filter Gray", Gmagnotude);

	waitKey(0);
}

// Laplacian Filter
void lab::lab3_5() {
	string imageName = "..\\image\\moon_blur.png";
	int ksize = 3;
	int half = ksize >> 1;
	float temp1, c = 1.0;

	Mat image = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	Mat laplacian_image = Mat::zeros(image.size(), CV_8U);
	Mat sharpen_image = Mat::zeros(image.size(), CV_8U);

	float kernel[3][3] = { {0, -1, 0}, {-1, 4, -1},{0, -1, 0} };

	for (int y = half; y < image.rows - half; y++) {
		for (int x = half; x < image.cols - half; x++) {
			temp1 = 0;
			for (int i = 0; i < ksize; i++) {
				for (int j = 0; j < ksize; j++) {
					temp1 += image.at<uchar>(y + (i - half), x + (j - half)) * kernel[i][j];

					laplacian_image.at<uchar>(y, x) = saturate_cast<uchar>(temp1);
					sharpen_image.at<uchar>(y, x) = saturate_cast<uchar>(image.at<uchar>(y, x) + c * temp1);
				}
			}
		}
	}

	imshow("Laplacian Filter Gray", laplacian_image);
	imshow("Enhanced Gray", sharpen_image);

	waitKey(0);
}