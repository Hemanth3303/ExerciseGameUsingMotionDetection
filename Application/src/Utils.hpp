#pragma once

#include "Constants.hpp"

#include <opencv2/opencv.hpp>
#include <raylib.h>

class Utils {
public:
	// converts opencv frame to raylib texture
	static const Texture& GetRaylibTexture(const cv::Mat& opencvFrame);
private:
	static Texture s_Texture;
	static Image s_Image;
	static cv::Mat s_LocalFrame;
};