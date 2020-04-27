#include "lab.h"

using namespace lab;

void showImage(std::string src) {
	cv::imshow("Origin", cv::imread(src.c_str(), cv::IMREAD_COLOR));
}

void show() {
	// 비교
	showImage("..\\image\\lena_noise.png");
	lab3_3_1();
	lab3_3_2();
}

int main() {
	//show();
	//showImage("..\\image\\moon_blur.png");
	lab3_3_3();

	return 0;
}