#include <opencv2/opencv.hpp>
#include <raylib.h>

#include <iostream>
#include <vector>

// Use discrete GPU by default.
#if defined(_WIN32) || defined(_WIN64)
extern "C" {
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

int main() {
	InitWindow(960, 540, "OpenCV-Raylib-Test");
	SetTraceLogLevel(LOG_WARNING);

	cv::Mat frame, frameOutputToRaylib;
	cv::VideoCapture videoCapture(0);

	Image raylibFrameImage;
	Texture raylibFrameTexture;

	if (!videoCapture.isOpened()) {
		std::cerr << "No video stream detected\n";
	}

	while (!WindowShouldClose()) {
		videoCapture >> frame;
		if (frame.empty()) {
			std::cerr << "Frame is empty\n";
		}

		cv::Mat grayFrame;

		cv::cvtColor(frame, frameOutputToRaylib, cv::COLOR_BGR2RGB);
		cv::flip(frameOutputToRaylib, frameOutputToRaylib, 1);
		raylibFrameImage.data = frameOutputToRaylib.ptr();
		raylibFrameImage.width = frameOutputToRaylib.cols;
		raylibFrameImage.height = frameOutputToRaylib.rows;
		raylibFrameImage.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
		raylibFrameImage.mipmaps = 1;

		BeginDrawing();
		ClearBackground(BLACK);
		
		raylibFrameTexture = LoadTextureFromImage(raylibFrameImage);
		DrawTexture(raylibFrameTexture, 0, 0, WHITE);
		DrawFPS(10, 10);
		DrawRectangle(500, 200, 300, 200, RED);
		DrawRectangle(500, 200, 250, 150, GREEN);
		DrawRectangle(500, 200, 200, 100, BLUE);

		EndDrawing();
		UnloadTexture(raylibFrameTexture);
	}

	videoCapture.release();

	CloseWindow();
	return 0;
}