#pragma once

#include "GameObject.hpp"

#include <raylib.h>

class Player {
public:
	Player();
	~Player();

	void update(const float deltaTime);

	inline const Vector3& getPosition() const { return m_GameObject.position; }
	inline const Vector3& getSize() const { return m_GameObject.size; }
	inline const Color& getColor() const { return m_GameObject.color; }
private:
	static constexpr float JUMP_SPEED = 30.0f;
	static constexpr float GRAVITY = 60.0f;
	static constexpr float GROUND_POS = 3.0f;
	float m_Dy = 0.0f;
	GameObject m_GameObject;
};