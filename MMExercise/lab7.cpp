#include "lab.h"

using namespace cv;
using namespace std;

void lab::lab7_1()
{
	VideoCapture cap(0);

	if (!cap.isOpened())
		return;

	Mat edges;
	namedWindow("edges", 1);

	while (waitKey(30) < 0)
	{
		Mat frame;
		cap >> frame;
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 50, 3);
		imshow("edges", edges);
	}
}

void lab::lab7_2()
{
	VideoCapture cap(0);

	if (!cap.isOpened())
		return;

	namedWindow("edges", 1);

	while (waitKey(30) < 0)
	{
		Mat frame;
		cap >> frame;

		Point2f srcTri[3], dstTri[3];

		Mat warp_mat(2, 3, CV_32FC1);

		srcTri[0] = Point2f(0, 0);
		srcTri[1] = Point2f(frame.cols - 1, 0);
		srcTri[2] = Point2f(0, frame.rows - 1);

		dstTri[0] = Point2f(frame.cols * 0.0, frame.rows * 0.33);
		dstTri[1] = Point2f(frame.cols * 0.85, frame.rows * 0.25);
		dstTri[2] = Point2f(frame.cols * 0.15, frame.rows * 0.7);

		warp_mat = getAffineTransform(srcTri, dstTri);

		warpAffine(frame, frame, warp_mat, frame.size());

		imshow("edges", frame);
	}
}

void lab::lab7_3()
{
	VideoCapture cap(0);
	string imageName = "..\\image\\moon.jpg";
	Mat img = imread(imageName, IMREAD_COLOR);

	if (!cap.isOpened())
		return;

	namedWindow("edges", 1);

	while (waitKey(30) < 0)
	{
		Mat frame;
		Mat xf;
		img.copyTo(xf);

		cap >> frame;
		resize(frame, frame, Size(img.cols, img.rows));

		cvtColor(frame, frame, COLOR_BGR2YCrCb);
		cvtColor(xf, xf, COLOR_BGR2YCrCb);

		Vec3b t;

		for (int y = 0; y < img.rows; y++) {
			for (int x = 0; x < img.cols; x++) {
				t = frame.at<Vec3b>(y, x);

				if (t[0] < 140 && t[1] < 180 && t[2] < 140) {
					xf.at<Vec3b>(y, x) = frame.at<Vec3b>(y, x);
				}
			}
		}

		cvtColor(xf, xf, COLOR_YCrCb2BGR);

		imshow("edges", xf);
	}
}