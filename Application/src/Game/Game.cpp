#include "Game.hpp"

float Game::s_DeltaTime = 0.0f;
std::shared_ptr<Camera3D> Game::s_Camera;
std::shared_ptr<Player> Game::s_Player;
std::shared_ptr<GameObject> Game::s_LeftLane, Game::s_CenterLane, Game::s_RightLane;
std::shared_ptr<GameObject> Game::s_Obstacle;
RenderTexture2D Game::s_GameTexture;
std::int64_t Game::s_PlayerScore = 0;
std::string Game::s_ScoreText = "";

void Game::Init() {
	s_Camera = std::make_shared<Camera3D>();
	s_Player = std::make_shared<Player>();
	s_LeftLane = std::make_shared<GameObject>(Vector3(leftLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 200.0f), Color(118, 85, 43, 255));
	s_CenterLane = std::make_shared<GameObject>(Vector3(centerLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 200.0f), Color(182, 159, 102, 255));
	s_RightLane = std::make_shared<GameObject>(Vector3(rightLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 200.0f), Color(118, 85, 43, 255));
	s_Obstacle=std::make_shared<GameObject>(Vector3(0.0f, 8.0f, -20.0f), Vector3(1.0f, 1.0f, 1.0f), VIOLET);


	s_GameTexture = LoadRenderTexture(gameWidth, winHeight);

	s_Camera->position = { 0.0f, 10.0f, 25.0f };
	s_Camera->target = { s_Player->getPosition().x, s_Player->getPosition().y + 5.0f, s_Player->getPosition().z };
	s_Camera->fovy = 60.0f;
	s_Camera->projection = CAMERA_PERSPECTIVE;
	s_Camera->up = { 0.0f, 1.0f, 0.0f };
}

void Game::Deinit() {

}

void Game::Update() {
	s_DeltaTime = GetFrameTime();
	UpdateCameraPro(s_Camera.get(), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.0f);
	s_Player->update(s_DeltaTime);

	float distance = Vector3Distance(s_Obstacle->position, s_Camera->position);
	float scale = Clamp(1.0f / distance, 0.001f, 0.4f);
	float fixedSize = 0.2f;

	s_Obstacle->size.x = fixedSize * scale * s_Camera->fovy;
	s_Obstacle->size.y = fixedSize * scale * s_Camera->fovy;
	s_Obstacle->size.z = fixedSize * scale * s_Camera->fovy;

	s_Obstacle->position.z += 10.0f * s_DeltaTime;

	if (s_Obstacle->position.z > 16) {
		s_Obstacle->position.z = -20.0f;
		s_PlayerScore++;
	}
	
	// std::cout << s_Obstacle->position.z << ", " << s_Player->getPosition().z << "\n";
}

void Game::Render() {
	BeginTextureMode(s_GameTexture);
	ClearBackground(Color(0, 191, 255, 255)); // skyblue color rgba
	BeginMode3D(*s_Camera);

	DrawCubeV(s_LeftLane->position, s_LeftLane->size, s_LeftLane->color);
	DrawCubeV(s_CenterLane->position, s_CenterLane->size, s_CenterLane->color);
	DrawCubeV(s_RightLane->position, s_RightLane->size, s_RightLane->color);

	DrawCubeV(s_Obstacle->position, s_Obstacle->size, s_Obstacle->color);
	DrawCubeV(s_Player->getPosition(), s_Player->getSize(), s_Player->getColor());

	EndMode3D();

	// 2d stuff
	s_ScoreText = "Score: " + std::to_string(s_PlayerScore) + " | FPS: " + std::to_string(GetFPS());
	DrawText(s_ScoreText.c_str(), 10, 10, 32, RED);
	EndTextureMode();
}
