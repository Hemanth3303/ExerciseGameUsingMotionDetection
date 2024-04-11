#include "MotionDetection.hpp"

cv::VideoCapture MotionDetection::s_VideoCapture(0); // 0 means default camera
cv::Mat MotionDetection::s_Frame;

cv::Mat processingFrame;
cv::Ptr<cv::BackgroundSubtractorMOG2> backgroundSubtractor;
cv::Mat kernel;
cv::Mat edges;
cv::HOGDescriptor hog;

std::vector<cv::Rect> bounds;

std::vector<std::vector<cv::Point>> contours;
std::vector<cv::Vec4i> hierarchy;

void MotionDetection::Init() {
	if (!s_VideoCapture.isOpened()) {
		std::cerr << "No video stream detected\n";
	}
	//s_VideoCapture.set(cv::CAP_PROP_FPS, 60);
	
	backgroundSubtractor = cv::createBackgroundSubtractorMOG2();
	kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));

	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}

void MotionDetection::Deinit() {
	s_VideoCapture.release();
}

void MotionDetection::Run() {
	s_VideoCapture >> s_Frame;
	if (s_Frame.empty()) {
		std::cerr << "Frame is empty\n";
	}

	backgroundSubtractor->apply(s_Frame, processingFrame);
	cv::flip(processingFrame, processingFrame, 1);
	cv::morphologyEx(processingFrame, processingFrame, cv::MORPH_OPEN, kernel);
	
	//cv::resize(processingFrame, processingFrame, cv::Size(640, 480));
	//hog.detectMultiScale(processingFrame, bounds);
	//for (size_t i = 0; i < bounds.size(); i++) {
	//	cv::rectangle(processingFrame, bounds[i], cv::Scalar(0, 255, 255), 2);
	//}

	//cv::cvtColor(s_Frame, processingFrame, cv::COLOR_BGR2GRAY);
	cv::Canny(processingFrame, edges, 150, 200);

	cv::findContours(edges, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

	for (size_t i = 0; i < contours.size(); i++) {
		if (cv::contourArea(contours[i]) > 100) {
			cv::drawContours(processingFrame, contours, i, cv::Scalar(255, 0, 0), 3);
		}
	}

	cv::imshow("processing frame", processingFrame);
}
