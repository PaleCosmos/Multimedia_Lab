#include "lab.h"

using namespace lab;

void showImage(std::string src) {
	cv::imshow("Origin", cv::imread(src.c_str(), cv::IMREAD_COLOR));
}

int main() {

	// 비교
	showImage("..\\image\\lena_noise.png");
	lab3_3_1();
	lab3_3_2();

	return 0;
}