#include "Application.hpp"
#include "Constants.hpp"

#include <iostream>

Application::Application(int32_t width, int32_t height, const std::string& title) 
	: m_Width(width), m_Height(height), m_Title(title) {

	init();
}

Application::~Application() {
	deinit();
}

void Application::run() {
	GameObject obstacle(Vector3(0.0f, 8.0f, -20.0f), Vector3(1.0f, 1.0f, 1.0f), VIOLET);

	while (!WindowShouldClose()) {
		// update
		m_DeltaTime = GetFrameTime();
		UpdateCameraPro(m_Camera.get(), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.0f);
		m_Player->update(m_DeltaTime);

		float distance = Vector3Distance(obstacle.position, m_Camera->position);
		float scale = Clamp(1.0f / distance, 0.001f, 0.4f);
		float fixedSize = 0.2f;

		obstacle.size.x = fixedSize * scale * m_Camera->fovy;
		obstacle.size.y = fixedSize * scale * m_Camera->fovy;
		obstacle.size.z = fixedSize * scale * m_Camera->fovy;

		obstacle.position.z += 10.0f * m_DeltaTime;

		if (obstacle.position.z > 16) {
			obstacle.position.z = -20.0f;
			m_PlayerScore++;
		}

		// std::cout << obstacle.position.z << ", " << m_Player->getPosition().z << "\n";

		// TODO: Fix rendering order

		// render
		BeginDrawing();
		ClearBackground(Color(0, 191, 255, 255)); // skyblue color rgba
		BeginMode3D(*m_Camera);

		DrawCubeV(m_LeftLane->position, m_LeftLane->size, m_LeftLane->color);
		DrawCubeV(m_CenterLane->position, m_CenterLane->size, m_CenterLane->color);
		DrawCubeV(m_RightLane->position, m_RightLane->size, m_RightLane->color);

		DrawCubeV(obstacle.position, obstacle.size, obstacle.color);
		DrawCubeV(m_Player->getPosition(), m_Player->getSize(), m_Player->getColor());
		
		EndMode3D();
		// 2d stuff
		std::string scoreText = "Score: " + std::to_string(m_PlayerScore);
		DrawText(scoreText.c_str(), 10, 10, 32, RED);
		EndDrawing();
	}
}

void Application::init() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(m_Width, m_Height, m_Title.c_str());

	m_Camera = std::make_shared<Camera3D>();
	m_Player = std::make_shared<Player>();
	m_LeftLane = std::make_shared<GameObject>(Vector3(leftLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 200.0f), Color(118, 85, 43, 255));
	m_CenterLane = std::make_shared<GameObject>(Vector3(centerLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 200.0f), Color(182, 159, 102, 255));
	m_RightLane = std::make_shared<GameObject>(Vector3(rightLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 200.0f), Color(118, 85, 43, 255));

	m_Camera->position = { 0.0f, 10.0f, 25.0f };
	m_Camera->target = { m_Player->getPosition().x, m_Player->getPosition().y + 5.0f, m_Player->getPosition().z };
	m_Camera->fovy = 60.0f;
	m_Camera->projection = CAMERA_PERSPECTIVE;
	m_Camera->up = { 0.0f, 1.0f, 0.0f };
}

void Application::deinit() {
	CloseWindow();
}
