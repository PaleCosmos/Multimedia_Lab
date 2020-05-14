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

int main() {
	std::string imageName = "..\\image\\gg.jpg";
	std::string imageName2 = "..\\image\\moon.jpg";
	showImage(imageName, "chroma");
	showImage(imageName2, "mooon");
	lab5_1();

	return 0;
}