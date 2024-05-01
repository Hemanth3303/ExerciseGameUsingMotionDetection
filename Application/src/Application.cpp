#include "Application.hpp"
#include "Constants.hpp"

#include <iostream>

Application::Application(std::int32_t width, std::int32_t height, const std::string& title) 
	: m_Width(width), m_Height(height), m_Title(title) {

	init();
}

Application::~Application() {
	deinit();
}

void Application::run() {

	while (!WindowShouldClose()) {
		MotionDetection::Run();
		
		// update
		Game::Update();
		m_MotionBodyCenter = Utils::GetMotionCenter();
		// render
		Game::Render();

		// draw the video texture and game texture to screen
		BeginDrawing();
		ClearBackground(WHITE);
		m_VideoTexture = Utils::GetRaylibTexture(MotionDetection::GetFrame());
		m_GameTexture = Game::GetGameTexture();

		DrawTexture(m_VideoTexture, 0, 0, WHITE);
		DrawTextureRec(
			m_GameTexture, 
			Rectangle(0.0f, 0.0f, static_cast<float>(gameWidth), static_cast<float>(-m_GameTexture.height)), 
			Vector2(static_cast<float>(winWidth - gameWidth), 0.0f), 
			WHITE
		);

		DrawLineV(m_ReferenceCenter, m_MotionBodyCenter, GREEN);
		DrawCircleV(m_ReferenceCenter, 10, RED);
		DrawCircleV(m_MotionBodyCenter, 10, BLUE);

		Game::ControlPlayerMovement(m_ReferenceCenter, m_MotionBodyCenter);
		
		EndDrawing();
		UnloadTexture(m_VideoTexture);
	}
}

void Application::init() {
	InitWindow(m_Width, m_Height, m_Title.c_str());
	SetTraceLogLevel(LOG_WARNING);
	SetTargetFPS(30);

	MotionDetection::Init();
	Game::Init();

	m_MotionBodyCenter = Vector2(videoWidth / 2.0f, winHeight / 2.0f);
	m_ReferenceCenter = Vector2(videoWidth / 2.0f, winHeight / 2.0f + 50.0f);
}

void Application::deinit() {
	Game::Deinit();
	MotionDetection::Deinit();
	CloseWindow();
}
