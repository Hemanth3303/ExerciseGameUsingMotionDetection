#include "Player.hpp"
#include "Game.hpp"
#include "Constants.hpp"

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
	if(IsKeyPressed(KEY_A) && m_GameObject.position.x>leftLanePos) {
		m_GameObject.position.x -= 10.0f;
	}
	if (IsKeyPressed(KEY_D) && m_GameObject.position.x < rightLanePos) {
		m_GameObject.position.x += 10.0f;
	}
	
}