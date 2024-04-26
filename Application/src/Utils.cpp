#include "Utils.hpp"

Texture Utils::s_Texture;
Image Utils::s_Image;
cv::Mat Utils::s_LocalFrame;

const Texture& Utils::GetRaylibTexture(const cv::Mat& opencvFrame) {
	// opencv stores frames in bgr (blue, green, red) format
	// so converting to rgb (red, green, blue)
	cv::cvtColor(opencvFrame, s_LocalFrame, cv::COLOR_BGR2RGB);
	cv::resize(s_LocalFrame, s_LocalFrame, cv::Size(videoWidth, winHeight));

	// create a raylib image buffer with the opencv frame
	s_Image.data = s_LocalFrame.ptr();
	s_Image.width = s_LocalFrame.cols;
	s_Image.height = s_LocalFrame.rows;
	s_Image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
	s_Image.mipmaps = 1;

	s_Texture = LoadTextureFromImage(s_Image);
	return s_Texture;
}

const Vector2 Utils::GetMotionCenter() {
	if (!MotionDetection::GetMotionCenter().x && !MotionDetection::GetMotionCenter().y) { 
		return Vector2(videoWidth / 2, winHeight / 2);
	}

	// mapping from processing frame size to video size on screen
	cv::Size sizeOfFrame = MotionDetection::GetProcessingFrameSize();
	return Vector2(
		MotionDetection::GetMotionCenter().x * videoWidth / sizeOfFrame.width,
		MotionDetection::GetMotionCenter().y * winHeight / sizeOfFrame.height
	);
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec2) {
	stream << "[X: " << vec2.x << ", Y: " << vec2.y << "]\n";
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vector3& vec3) {
	stream << "[X: " << vec3.x << ", Y: " << vec3.y << ", Z: " << vec3.z << "]\n";
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vector4& vec4) {
	stream << "[X: " << vec4.x << ", Y: " << vec4.y << ", Z: " << vec4.z << ", W: " << vec4.w << "]\n";
	return stream;
}
