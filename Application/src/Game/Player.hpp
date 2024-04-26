#pragma once

#include "GameObject.hpp"

#include <raylib.h>

#include <array>

enum class Inputs : std::int32_t {
	Unknown = -1,
	Left = 0,
	Right = 1,
	Jump = 2,
};

class Player {
public:
	Player();
	~Player();

	void update(const float deltaTime);

	inline const Vector3& getPosition() const { return m_GameObject.position; }
	inline const Vector3& getSize() const { return m_GameObject.size; }
	inline const Color& getColor() const { return m_GameObject.color; }

	inline void setMovement(Inputs input, bool value) { m_MovementInputs[static_cast<std::int32_t>(input)] = value; }
private:
	inline bool shouldMove(Inputs input) { return m_MovementInputs[static_cast<std::int32_t>(input)]; }
private:
	static constexpr float JUMP_SPEED = 30.0f;
	static constexpr float GRAVITY = 60.0f;
	static constexpr float GROUND_POS = 3.0f;
	float m_Dy = 0.0f;
	GameObject m_GameObject;
	std::array<bool, 3> m_MovementInputs{};
};