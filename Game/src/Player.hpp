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
	GameObject m_GameObject;
};