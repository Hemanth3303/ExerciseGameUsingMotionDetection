#include "Player.hpp"
#include "../Constants.hpp"

Player::Player() 
	: m_GameObject({ 0.0f, GROUND_POS, 0.0f },{2.0f, 5.0f, 1.0f}, RED) {

	for (bool& input : m_MovementInputs) {
		input = false;
	}
}

Player::~Player() {

}

void Player::update(const float deltaTime) {
	// jumping based on gravity
	m_Dy -= GRAVITY * deltaTime;
	if (shouldMove(Inputs::Jump) && (m_GameObject.position.y <= GROUND_POS)) {
		m_Dy = JUMP_SPEED;
	}
	m_GameObject.position.y += m_Dy * deltaTime;
	if (m_GameObject.position.y < GROUND_POS) {
		m_GameObject.position.y = GROUND_POS;
		m_Dy = 0.0f;
	}

	// left-right movement
	if(shouldMove(Inputs::Left) && m_GameObject.position.x>leftLanePos) {
		m_GameObject.position.x -= 10.0f;
	}
	if (shouldMove(Inputs::Right) && m_GameObject.position.x < rightLanePos) {
		m_GameObject.position.x += 10.0f;
	}

	for (bool& input : m_MovementInputs) {
		input = false;
	}
}