#include "lab.h"

using namespace cv;
using namespace std;

void lab::lab6_1()
{
	string imageName = "..\\image\\moon.jpg";

	Mat src = imread(imageName, IMREAD_COLOR);

	Point2f srcTri[3], dstTri[3];

	Mat warp_mat(2, 3, CV_32FC1);

	Mat warp_dst = Mat::zeros(src.rows, src.cols, src.type());

	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);

	dstTri[0] = Point2f(src.cols * 0.0, src.rows * 0.33);
	dstTri[1] = Point2f(src.cols * 0.85, src.rows * 0.25);
	dstTri[2] = Point2f(src.cols * 0.15, src.rows * 0.7);

	warp_mat = getAffineTransform(srcTri, dstTri);

	warpAffine(src, warp_dst, warp_mat, warp_dst.size());
	imshow("img", warp_dst);

	waitKey(0);
}

void lab::lab6_2()
{
	string imageName = "..\\image\\moon.jpg";

	Mat input = imread(imageName, IMREAD_COLOR);

	Point2f  inputQuad[4], outputQuad[4];

	Mat warp_mat(2, 4, CV_32FC1);

	Mat output = Mat::zeros(input.rows, input.cols, input.type());

	inputQuad[0] = Point2f(0, 0);
	inputQuad[1] = Point2f(input.cols - 1, 0);
	inputQuad[2] = Point2f(input.cols - 1, input.rows - 1);
	inputQuad[3] = Point2f(0, input.rows - 1);

	outputQuad[0] = Point2f(30, 60);
	outputQuad[1] = Point2f(input.cols - 50, +50);
	outputQuad[2] = Point2f(input.cols - 100, input.rows - 50);
	outputQuad[3] = Point2f(50, input.rows - 50);

	warp_mat = getPerspectiveTransform(inputQuad, outputQuad);

	warpPerspective(input, output, warp_mat, output.size());
	imshow("img", output);

	waitKey(0);
}

// Nearest Neighbor Interpolation
void lab::lab6_3(int a, char** args)
{
	double x, y;
	string outputFileName;

	if (a < 5)
	{
		cout << "Arguments NONO" << endl;
		return;
	}

	outputFileName = args[2];
	x = strtod(args[3], NULL);
	y = strtod(args[4], NULL);

	Mat dst, lib, src = imread(args[1], IMREAD_COLOR);

	resize(src, lib, Size(), x, y, INTER_NEAREST);

	dst = Mat::zeros(src.rows * y, src.cols * x, src.type());

	for (int h = 0; h < dst.rows; h++) {
		for (int w = 0; w < dst.cols; w++) {
			dst.at<Vec3b>(h, w) = src.at<Vec3b>(h / y, w / x);
		}
	}

	imshow("lib", lib);
	imshow("dst", dst);
	imwrite(outputFileName, dst);
	waitKey(0);
}

// Bilinear Interpolation
void lab::lab6_4(int a, char** args)
{
	double x, y, fx1, fx2, fy1, fy2;
	int px, py;
	string outputFileName;

	if (a < 5)
	{
		cout << "Arguments NONO" << endl;
		return;
	}

	outputFileName = args[2];
	x = strtod(args[3], NULL);
	y = strtod(args[4], NULL);

	Mat dst, lib, src = imread(args[1], IMREAD_COLOR);

	resize(src, lib, Size(), x, y, INTER_LINEAR);

	dst = Mat::zeros(src.rows * y, src.cols * x, src.type());

	for (int h = 0; h < dst.rows; h++) {
		for (int w = 0; w < dst.cols; w++) {
			px = (int)w / x;
			py = (int)h / y;

			if (px < src.cols - 1 && py < src.rows - 1) {

				fx1 = (double)w / x - (double)px;
				fx2 = 1 - fx1;
				fy1 = (double)h / y - (double)py;
				fy2 = 1 - fy1;

				dst.at<Vec3b>(h, w) =
					fx2 * fy2 * src.at<Vec3b>(py, px) +
					fx1 * fy2 * src.at<Vec3b>(py, px + 1) +
					fx2 * fy1 * src.at<Vec3b>(py + 1, px) +
					fx1 * fy1 * src.at<Vec3b>(py + 1, px + 1);
			}
		}
	}

	imshow("lib", lib);
	imshow("dst", dst);
	imwrite(outputFileName, dst);
	waitKey(0);
}

// Bicubic Interpolation
void lab::lab6_5(int a, char** args)
{
	double x, y, fx1, fx2, fy1, fy2;
	int px, py;
	string outputFileName;

	if (a < 5)
	{
		cout << "Arguments NONO" << endl;
		return;
	}

	outputFileName = args[2];
	x = strtod(args[3], NULL);
	y = strtod(args[4], NULL);

	Mat dst, lib, src = imread(args[1], IMREAD_COLOR);

	resize(src, lib, Size(), x, y, INTER_CUBIC);

	dst = Mat::zeros(src.rows * y, src.cols * x, src.type());

	for (int h = 0; h < dst.rows; h++) {
		for (int w = 0; w < dst.cols; w++) {
			//±ÍÂú¾Æ¿ä
		}
	}

	imshow("lib", lib);
	imshow("dst", dst);
	//imwrite(outputFileName, dst);
	waitKey(0);
}