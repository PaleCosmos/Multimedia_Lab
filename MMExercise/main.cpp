#include "lab.h"

using namespace lab;

void showImage(std::string src, std::string name) {
	cv::imshow(name, cv::imread(src.c_str(), cv::IMREAD_COLOR));
}

void show() {
	// 비교
	showImage("..\\image\\lena_noise.png", "lena_noise");
	lab3_3_1();
	lab3_3_2();
}

int main(int arg, char** args) {
	lab9_1();

	return 0;
}