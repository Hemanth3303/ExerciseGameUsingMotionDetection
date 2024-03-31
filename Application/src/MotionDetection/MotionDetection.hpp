#pragma once

#include <opencv2/opencv.hpp>

class MotionDetection {
public:
	static void Init();
	static void Deinit();

	static void Run();

	inline static const cv::Mat& GetFrame() { return s_Frame; }
private:
	static cv::VideoCapture s_VideoCapture;
	static cv::Mat s_Frame;
};