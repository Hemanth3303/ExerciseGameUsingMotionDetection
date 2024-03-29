#pragma once

#include "GameObject.hpp"

#include <raylib.h>

class Player {
public:
	Player();
	~Player();

	void update(const float deltaTime);
	void moveLeft();
	void moveRight();
	void jump();

	inline const Vector3& getPosition() const { return m_GameObject.position; }
	inline const Vector3& getSize() const { return m_GameObject.size; }
	inline const Color& getColor() const { return m_GameObject.color; }
private:
	static constexpr float JUMP_SPEED = 30.0f;
	static constexpr float ACCELERATION = 60.0f;
	static constexpr float GRAVITY = 60.0f;
	static constexpr float GROUND_POS = 3.0f;
	static constexpr float MAX_SPEED = 40.0f;
	static constexpr float DAMPING = 0.85f;
	static constexpr float CAMERA_BOUNDS_X = 13.0f;
	float m_Dy = 0.0f;
	float m_HorizontalInput = 0.0f;
	float m_HorizontalSpeed = 0.0f;
	float deceleration = 0.0f;
	GameObject m_GameObject;
};