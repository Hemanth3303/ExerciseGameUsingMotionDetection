#include "Game.hpp"

float Game::s_DeltaTime = 0.0f;
std::shared_ptr<Camera3D> Game::s_Camera;
std::shared_ptr<Player> Game::s_Player;
std::shared_ptr<GameObject> Game::s_LeftLane, Game::s_CenterLane, Game::s_RightLane;
std::vector<GameObject> Game::s_Coins;
RenderTexture2D Game::s_GameTexture;
std::int64_t Game::s_PlayerScore = 0;
std::string Game::s_ScoreText = "";

void Game::Init() {
	s_Camera = std::make_shared<Camera3D>();
	s_Player = std::make_shared<Player>();
	s_LeftLane = std::make_shared<GameObject>(Vector3(leftLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 300.0f), Color(118, 85, 43, 255));
	s_CenterLane = std::make_shared<GameObject>(Vector3(centerLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 300.0f), Color(182, 159, 102, 255));
	s_RightLane = std::make_shared<GameObject>(Vector3(rightLanePos, 0.0f, 0.0), Vector3(10.f, 1.0f, 300.0f), Color(118, 85, 43, 255));

	s_GameTexture = LoadRenderTexture(gameWidth, winHeight);

	s_Camera->position = { 0.0f, 13.0f, 20.0f };
	s_Camera->target = { s_Player->getPosition().x, s_Player->getPosition().y + 5.0f, s_Player->getPosition().z };
	s_Camera->fovy = 60.0f;
	s_Camera->projection = CAMERA_PERSPECTIVE;
	s_Camera->up = { 0.0f, 1.0f, 0.0f };
}

void Game::Deinit() {

}

void Game::Update() {
	s_DeltaTime = GetFrameTime();
	ManageCoinSpawn();
	UpdateCameraPro(s_Camera.get(), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.0f);
	s_Player->update(s_DeltaTime);
	for (GameObject& coin : s_Coins) {
		coin.position.z += 10.0f * s_DeltaTime;
	}
	for (std::size_t i = 0; i < s_Coins.size(); i++) {
		if (s_Coins[i].position.z > 30) {
			s_Coins.erase(s_Coins.begin() + i);
			break;
		}
		if (PlayerCoinCollision(s_Coins[i])) {
			s_Coins.erase(s_Coins.begin() + i);
			s_PlayerScore++;
			break;
		}
	}
}

void Game::Render() {
	BeginTextureMode(s_GameTexture);
	ClearBackground(Color(0, 191, 255, 255)); // skyblue color rgba
	BeginMode3D(*s_Camera);

	DrawCubeV(s_LeftLane->position, s_LeftLane->size, s_LeftLane->color);
	DrawCubeV(s_CenterLane->position, s_CenterLane->size, s_CenterLane->color);
	DrawCubeV(s_RightLane->position, s_RightLane->size, s_RightLane->color);

	for (const GameObject& coin : s_Coins) {
		DrawCubeV(coin.position, coin.size, coin.color);
	}
	DrawCubeV(s_Player->getPosition(), s_Player->getSize(), s_Player->getColor());

	EndMode3D();

	// 2d stuff
	s_ScoreText = "Score: " + std::to_string(s_PlayerScore) + " | FPS: " + std::to_string(GetFPS());
	DrawText(s_ScoreText.c_str(), 10, 10, 32, RED);
	EndTextureMode();
}

void Game::ControlPlayerMovement(const Vector2& referenceCenter, const Vector2& motionbodyCenter) {

	float dx = motionbodyCenter.x - referenceCenter.x;
	float dy = motionbodyCenter.y - referenceCenter.y;

	const float xThreshold = 80.0f;
	const float yThreshold = 45.0f;
	
	if (dx < -xThreshold) {
		s_Player->setMovement(Inputs::Left, true);
		//std::cout << "[LEFT]\n";
	}
	else if (dx > xThreshold) {
		s_Player->setMovement(Inputs::Right, true);
		//std::cout << "[RIGHT]\n";
	}
	else {
		s_Player->centerize();
		//std::cout << "[CENTER]\n";
	}

	if (dy < -yThreshold) {
		s_Player->setMovement(Inputs::Jump, true);
		//std::cout << "[JUMP]\n";
	}

	//std::cout << "DiffX: " << dx << "\n";
	//std::cout << "DiffY: " << dy << "\n";
}

bool Game::PlayerCoinCollision(const GameObject& coin) {
	const Vector3& playerPos = s_Player->getPosition();
	if (playerPos.y >= 8) {
		if ((coin.position.x <= -2.7f) && (playerPos.x <= -10.0f)) {
			if (coin.position.z > 14) {
				return true;
			}
		}
		else if (coin.position.x == 0.0f && playerPos.x == 0.0f) {
			if (coin.position.z > 8) {
				return true;
			}
		}
		else if (coin.position.x >= 2.7 && playerPos.x >= 10.0f) {
			if (coin.position.z > 14) {
				return true;
			}
		}
	}
		
	return false;
}

void Game::ManageCoinSpawn() {
	static float spawnTimer = 0.0f;
	constexpr static float threshold = 2.0f;

	spawnTimer += s_DeltaTime;

	if (spawnTimer > threshold) {
		spawnTimer = 0.0f;
		float coinXPos = GetRandomValue(-1, 1) * 2.7;
		for (std::int32_t i = 0; i < GetRandomValue(5, 10); i++) {
			s_Coins.emplace_back(Vector3(coinXPos, 12.0f, -20.0f - (i * 2.0f)), Vector3(0.25f, 0.25f, 0.25f), GOLD);
		}
	}
}
