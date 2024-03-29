#include "Player.hpp"
#include "Game.hpp"

#include <cmath>
#include <algorithm>
#include <iostream>

Player::Player() 
	: m_GameObject({ 0.0f, GROUND_POS, 0.0f },{2.0f, 5.0f, 1.0f}, RED) {

}

Player::~Player() {

}

void Player::update(const float deltaTime) {
	// jumping based on gravity
	m_Dy -= GRAVITY * deltaTime;
	if (IsKeyDown(KEY_SPACE) && (m_GameObject.position.y <= GROUND_POS)) {
		m_Dy = JUMP_SPEED;
	}
	m_GameObject.position.y += m_Dy * deltaTime;
	if (m_GameObject.position.y < GROUND_POS) {
		m_GameObject.position.y = GROUND_POS;
		m_Dy = 0.0f;
	}

	// left-right movement
	m_HorizontalInput = 0.0f;
	if (IsKeyDown(KEY_A)) {
		m_HorizontalInput -= 1.0f;
	}
	if (IsKeyDown(KEY_D)) {
		m_HorizontalInput += 1.0f;
	}

	// Apply deceleration or friction when no movement keys are pressed
	if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
		if (m_HorizontalSpeed > 0.0f) {
			deceleration = -DAMPING * ACCELERATION;
		}
		else if (m_HorizontalSpeed < 0.0f) {
			deceleration = DAMPING * ACCELERATION;
		}
	}

	m_HorizontalSpeed += (m_HorizontalInput * ACCELERATION + deceleration) * deltaTime;
	m_HorizontalSpeed *= std::pow(DAMPING, deltaTime);
	m_HorizontalSpeed = std::clamp(m_HorizontalSpeed, -MAX_SPEED, MAX_SPEED);

	m_GameObject.position.x += m_HorizontalSpeed * deltaTime;

	if (m_GameObject.position.x < -CAMERA_BOUNDS_X) {
		m_GameObject.position.x = -CAMERA_BOUNDS_X;
		m_HorizontalSpeed = 0.0f;
	}
	else if (m_GameObject.position.x > CAMERA_BOUNDS_X) {
		m_GameObject.position.x = CAMERA_BOUNDS_X;
		m_HorizontalSpeed = 0.0f;
	}
}
