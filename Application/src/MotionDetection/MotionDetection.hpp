#pragma once

#include <opencv2/opencv.hpp>
#include "../Constants.hpp"

class MotionDetection {
public:
	static void Init();
	static void Deinit();

	static void Run();

	inline static const cv::Mat& GetFrame() { return s_Frame; }
	inline static const cv::Point& GetMotionCenter() { return s_MotionCenter; }
	inline static const cv::Size GetProcessingFrameSize() { return s_ProcessingFrame.size(); }
private:
	static cv::VideoCapture s_VideoCapture;
	static cv::Mat s_Frame;
	static cv::Mat s_ProcessingFrame;
	static cv::Mat s_BackSubKernel;
	static cv::Ptr<cv::BackgroundSubtractorMOG2> s_BackgroundSubtractor;
	static cv::Point s_MotionCenter;
	static std::vector<std::vector<cv::Point>> s_Contours;
	static cv::Rect s_BoundingBox;
};