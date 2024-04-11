#include "MotionDetection.hpp"

cv::VideoCapture MotionDetection::s_VideoCapture(0); // 0 means default camera
cv::Mat MotionDetection::s_Frame;

cv::Mat processingFrame;
cv::Mat kernel;
cv::Ptr<cv::BackgroundSubtractorMOG2> pbacksub;

void MotionDetection::Init() {
	if (!s_VideoCapture.isOpened()) {
		std::cerr << "No video stream detected\n";
	}
	pbacksub = cv::createBackgroundSubtractorMOG2();
	kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
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

	cv::cvtColor(s_Frame, processingFrame, cv::COLOR_BGR2GRAY);

	pbacksub->apply(processingFrame, processingFrame);
	cv::morphologyEx(processingFrame, processingFrame, cv::MORPH_OPEN, kernel);

	// Find contours around the detected motion regions
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(processingFrame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// Find the bounding box that encompasses all contours
	cv::Rect boundingBox;
	for (const auto& contour : contours) {
		// Compute the bounding rectangle for the current contour
		cv::Rect contourBoundingBox = cv::boundingRect(contour);

		// Expand the overall bounding box to include the current contour
		boundingBox = boundingBox | contourBoundingBox;
	}

	cv::Point center = cv::Point(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2);

	// Draw the single bounding box covering the entire area with motion
	if (!boundingBox.empty()) {
		cv::rectangle(processingFrame, boundingBox, cv::Scalar(255, 0, 0), 2);
		cv::rectangle(s_Frame, boundingBox, cv::Scalar(255, 0, 0), 2);

		cv::circle(processingFrame, center, 10, cv::Scalar(255, 0, 0), cv::FILLED);
		cv::circle(s_Frame, center, 10, cv::Scalar(0, 0, 255), cv::FILLED);
	}


	cv::imshow("processingFrame", processingFrame);
}
