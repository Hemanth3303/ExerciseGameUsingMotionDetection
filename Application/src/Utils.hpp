#pragma once

#include "Constants.hpp"
#include "MotionDetection/MotionDetection.hpp"

#include <opencv2/opencv.hpp>
#include <raylib.h>

#include <iostream>

class Utils {
public:
	// converts opencv frame to raylib texture
	static const Texture& GetRaylibTexture(const cv::Mat& opencvFrame);

	// get center of detected moving human/object
	static const Vector2 GetMotionCenter();
private:
	static Texture s_Texture;
	static Image s_Image;
	static cv::Mat s_LocalFrame;
};

std::ostream& operator<<(std::ostream& stream, const Vector2& vec2);
std::ostream& operator<<(std::ostream& stream, const Vector3& vec3);
std::ostream& operator<<(std::ostream& stream, const Vector4& vec4);