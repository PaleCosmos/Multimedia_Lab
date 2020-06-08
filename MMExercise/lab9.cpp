#include "lab.h"

using namespace cv;
using namespace std;

void lab::lab9_1()
{
	int ksize = 3, ksize_h = ksize >> 1, RANGE = 16;
	int l = 1, r = l + 1;

	static Mat scenes[5] = {
		imread("..\\image\\tsukuba\\scene1.row3.col1.png", IMREAD_GRAYSCALE),
		imread("..\\image\\tsukuba\\scene1.row3.col2.png", IMREAD_GRAYSCALE),
		imread("..\\image\\tsukuba\\scene1.row3.col3.png", IMREAD_GRAYSCALE),
		imread("..\\image\\tsukuba\\scene1.row3.col4.png", IMREAD_GRAYSCALE),
		imread("..\\image\\tsukuba\\scene1.row3.col5.png", IMREAD_GRAYSCALE)
	};

	Mat left, right, disp;

	scenes[l].copyTo(left);
	scenes[r].copyTo(right);

	disp = Mat::zeros(left.rows, left.cols, left.type());

	float cost = 0;
	int min_cost;
	int best_disp, y = ksize_h, x, d, i, j;
	int lr = left.rows - ksize_h;
	int lc = left.cols - ksize_h;

	for (; y < lr; y++) {
		for (x = ksize_h; x < lc; x++) {
			best_disp = 0;
			min_cost = INT_MAX;

			for (d = 0; d <= RANGE; d++) {
				cost = 0;
				if (x - d < ksize_h)
					break;

				for (i = 0; i < ksize; i++) {
					for (j = 0; j < ksize; j++) {
						cost += pow(left.at<uchar>(y + (i - ksize_h), x + (j - ksize_h)) - right.at<uchar>(y + (i - ksize_h), x - d + (j - ksize_h)), 2);
					}
				}

				if (min_cost > cost) {
					min_cost = cost;
					best_disp = d;
				}
			}
			disp.at<uchar>(y, x) = best_disp;
		}
	}

	disp *= 10;

	imshow("Left", left);
	imshow("Right", right);
	imshow("Result", disp);

	waitKey(0);
}