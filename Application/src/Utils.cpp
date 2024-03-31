#include "Utils.hpp"

Texture Utils::s_Texture;
Image Utils::s_Image;
cv::Mat Utils::s_LocalFrame;

const Texture& Utils::GetRaylibTexture(const cv::Mat& opencvFrame) {
	// opencv stores frames in bgr (blue, green, red) format
	// so converting to rgb (red, green, blue)
	cv::cvtColor(opencvFrame, s_LocalFrame, cv::COLOR_BGR2RGB);
	cv::resize(s_LocalFrame, s_LocalFrame, cv::Size(videoWidth, winHeight));

	// flip the frame horizontally 
	cv::flip(s_LocalFrame, s_LocalFrame, 1);

	// create a raylib image buffer with the opencv frame
	s_Image.data = s_LocalFrame.ptr();
	s_Image.width = s_LocalFrame.cols;
	s_Image.height = s_LocalFrame.rows;
	s_Image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
	s_Image.mipmaps = 1;

	s_Texture = LoadTextureFromImage(s_Image);
	return s_Texture;
}
