#include "Game.hpp"
#include "Constants.hpp"

Game::Game(int32_t width, int32_t height, const std::string& title) 
	: m_Width(width), m_Height(height), m_Title(title) {

	init();
}

Game::~Game() {
	deinit();
}

void Game::run() {
	while (!WindowShouldClose()) {
		// update
		m_DeltaTime = GetFrameTime();
		//UpdateCamera(m_Camera.get(), CAMERA_THIRD_PERSON);
		m_Player->update(m_DeltaTime);

		// render
		BeginDrawing();
		ClearBackground(Color(0, 191, 255, 255));

		BeginMode3D(*m_Camera);

		DrawCubeV(m_Player->getPosition(), m_Player->getSize(), m_Player->getColor());
		DrawCubeV(m_LeftLane->position, m_LeftLane->size, m_LeftLane->color);
		DrawCubeV(m_CenterLane->position, m_CenterLane->size, m_CenterLane->color);
		DrawCubeV(m_RightLane->position, m_RightLane->size, m_RightLane->color);
		
		EndMode3D();

		EndDrawing();
	}
}

void Game::init() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(m_Width, m_Height, m_Title.c_str());

	m_Camera = std::make_shared<Camera3D>();
	m_Player = std::make_shared<Player>();
	m_LeftLane = std::make_shared<GameObject>(Vector3(leftLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 200.0f), Color(118, 85, 43, 255));
	m_CenterLane = std::make_shared<GameObject>(Vector3(centerLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 200.0f), Color(182, 159, 102, 255));
	m_RightLane = std::make_shared<GameObject>(Vector3(rightLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 200.0f), Color(118, 85, 43, 255));

	m_Camera->position = { 0.0f, 10.0f, 13.0f };
	m_Camera->target = { m_Player->getPosition().x, m_Player->getPosition().y + 5.0f, m_Player->getPosition().z };
	m_Camera->fovy = 60.0f;
	m_Camera->projection = CAMERA_PERSPECTIVE;
	m_Camera->up = { 0.0f, 1.0f, 0.0f };
}

void Game::deinit() {
	CloseWindow();
}
