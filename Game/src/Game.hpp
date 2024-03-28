#pragma once

#include <raylib.h>

#include <cstdint>
#include <string>

class Game {
public:
	Game(int32_t width, int32_t height, const std::string& title);
	~Game();

	void run();
private:
	int32_t m_Width, m_Height;
	std::string m_Title;
};