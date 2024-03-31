#include "MotionDetection.hpp"

cv::VideoCapture MotionDetection::s_VideoCapture(0); // 0 means default camera
cv::Mat MotionDetection::s_Frame;

void MotionDetection::Init() {
	if (!s_VideoCapture.isOpened()) {
		std::cerr << "No video stream detected\n";
	}
	//s_VideoCapture.set(cv::CAP_PROP_FPS, 60);
}

void MotionDetection::Deinit() {
	s_VideoCapture.release();
}

void MotionDetection::Run() {
	s_VideoCapture >> s_Frame;
	if (s_Frame.empty()) {
		std::cerr << "Frame is empty\n";
	}
}
