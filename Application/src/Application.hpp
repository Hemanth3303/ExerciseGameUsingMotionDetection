#pragma once

#include "Game/Game.hpp"
#include "MotionDetection/MotionDetection.hpp"
#include "Utils.hpp"

#include <raylib.h>

#include <cstdint>

class Application {
public:
	Application(std::int32_t width, std::int32_t height, const std::string& title);
	~Application();

	void run();
private:
	void init();
	void deinit();
private:
	std::int32_t m_Width, m_Height;
	std::string m_Title;
	Texture m_VideoTexture{};
	Texture m_GameTexture{};
	Vector2 m_MotionBodyCenter{};
};