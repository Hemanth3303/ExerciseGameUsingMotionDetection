#pragma once

#include "Player.hpp"
#include "GameObject.hpp"
#include "Constants.hpp"

#include <raylib.h>
#include <raymath.h>

#include "Utils.hpp"

#include <cstdint>
#include <string>
#include <memory>
#include <iostream>

class Game {
public:
	static void Init();
	static void Deinit();

	static void Update();
	static void Render();
	static void ControlPlayerMovement(const Vector2& referenceCenter, const Vector2& motionbodyCenter);

	inline static const Texture& GetGameTexture() { return s_GameTexture.texture; }
private:
	static float s_DeltaTime;
	static std::shared_ptr<Camera3D> s_Camera;
	static std::shared_ptr<Player> s_Player;
	static std::shared_ptr<GameObject> s_LeftLane, s_CenterLane, s_RightLane;
	static std::vector<GameObject> s_Coins;
	static RenderTexture2D s_GameTexture;
	static int64_t s_PlayerScore;
	static std::string s_ScoreText;
};