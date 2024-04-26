#include "MotionDetection.hpp"

cv::VideoCapture MotionDetection::s_VideoCapture(0); // 0 means default camera
cv::Mat MotionDetection::s_Frame;
cv::Mat MotionDetection::s_ProcessingFrame;
cv::Mat MotionDetection::s_BackSubKernel;
cv::Ptr<cv::BackgroundSubtractorMOG2> MotionDetection::s_BackgroundSubtractor;
cv::Point MotionDetection::s_MotionCenter;
std::vector<std::vector<cv::Point>> MotionDetection::s_Contours;
cv::Rect MotionDetection::s_BoundingBox;

void MotionDetection::Init() {
	if (!s_VideoCapture.isOpened()) {
		std::cerr << "No video stream detected\n";
	}
	s_BackgroundSubtractor = cv::createBackgroundSubtractorMOG2();
	s_BackSubKernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
}

void MotionDetection::Deinit() {
	s_VideoCapture.release();
}

void MotionDetection::Run() {
	s_VideoCapture >> s_Frame;
	if (s_Frame.empty()) {
		std::cerr << "Frame is empty\n";
	}

	// flip the frame horizontally 
	cv::flip(s_Frame, s_Frame, 1);

	cv::cvtColor(s_Frame, s_ProcessingFrame, cv::COLOR_BGR2GRAY);

	s_BackgroundSubtractor->apply(s_ProcessingFrame, s_ProcessingFrame);
	cv::morphologyEx(s_ProcessingFrame, s_ProcessingFrame, cv::MORPH_OPEN, s_BackSubKernel);

	// Find contours around the detected motion regions
	cv::findContours(s_ProcessingFrame, s_Contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// clear the bounding box every frame before calculations
	s_BoundingBox = cv::Rect();
	// Find the bounding box that encompasses all contours
	for (const auto& contour : s_Contours) {
		// Compute the bounding rectangle for the current contour
		cv::Rect contourBoundingBox = cv::boundingRect(contour);

		// Expand the overall bounding box to include the current contour
		s_BoundingBox = s_BoundingBox | contourBoundingBox;
	}

	s_MotionCenter = cv::Point(s_BoundingBox.x + s_BoundingBox.width / 2, s_BoundingBox.y + s_BoundingBox.height / 2);

	// Draw the single bounding box covering the entire area with motion
	if (!s_BoundingBox.empty()) {
		cv::rectangle(s_ProcessingFrame, s_BoundingBox, cv::Scalar(255, 0, 0), 2);
		cv::rectangle(s_Frame, s_BoundingBox, cv::Scalar(255, 0, 0), 2);

		cv::circle(s_ProcessingFrame, s_MotionCenter, 10, cv::Scalar(255, 0, 0), cv::FILLED);
	}


	// cv::imshow("s_ProcessingFrame", s_ProcessingFrame);
}
