#pragma once

#include "GameObject.hpp"
#include "Player.hpp"

#include <raylib.h>

#include <cstdint>
#include <string>
#include <memory>

class Game {
public:
	Game(int32_t width, int32_t height, const std::string& title);
	~Game();

	void run();
private:
	void init();
	void deinit();
private:
	int32_t m_Width, m_Height;
	std::string m_Title;
	float m_DeltaTime = 0.0f;
	std::shared_ptr<Camera3D> m_Camera;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<GameObject> m_LeftLane, m_CenterLane, m_RightLane;
	int64_t m_PlayerScore = 0;
};