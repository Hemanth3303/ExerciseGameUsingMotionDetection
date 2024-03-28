#include "Game.hpp"

Game::Game(int32_t width, int32_t height, const std::string& title) 
	: m_Width(width), m_Height(height), m_Title(title) {

	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(m_Width, m_Height, m_Title.c_str());
}

Game::~Game() {
	CloseWindow();
}

void Game::run() {
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawFPS(10, 10);

		EndDrawing();
	}
}
