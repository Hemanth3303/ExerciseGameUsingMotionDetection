#include "Player.hpp"

Player::Player() 
	: m_GameObject({ 0.0f, 3.0f, 0.0f },{1.0f, 5.0f, 2.0f}, RED) {

}

Player::~Player() {

}

void Player::update(const float deltaTime) {
	if (IsKeyDown(KEY_SPACE)) {
		m_GameObject.position.y += JUMP_SPEED * deltaTime;
	}
	if (IsKeyDown(KEY_A)) {
		m_GameObject.position.z -= MOVE_SPEED * deltaTime;
	}
	if (IsKeyDown(KEY_D)) {
		m_GameObject.position.z += MOVE_SPEED * deltaTime;
	}
}
