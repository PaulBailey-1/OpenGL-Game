#include "Player.h"

Player::Player(int winWidth, int winHeight) : camera(winWidth, winHeight) {
	
}

sf::Vector2i Player::updateMouse(sf::Vector2i mousePos) {
	camera.updateMouse(mousePos);
}

void Player::setElapsedTime(float deltaTime) {
	camera.setSpeed(deltaTime);
}

void Player::forward() {
	camera.forward();
}

void Player::backward() {
	camera.backward();
}

void Player::strafeLeft() {
	camera.strafeLeft();
}

void Player::strafeRight() {
	camera.strafeRight();
}
