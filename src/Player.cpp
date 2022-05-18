#include "Player.h"

Player::Player(int winWidth, int winHeight, Shader* shader_, glm::vec3 startingPos, float height_, const char* path) {

	camera = Camera(winWidth, winHeight, startingPos + glm::vec3(0.0, height_, 0.0));
	object = Object(path, shader_);

	shader = shader_;
	pos = startingPos;
	velocity = glm::vec3(0.0, 0.0, 0.0);

	height = height_;

	grounded = true;
}

sf::Vector2i Player::updateMouse(sf::Vector2i mousePos) {
	return camera.updateMouse(mousePos);
}

void Player::draw() {
	object.translate(pos);
	object.draw();
}

void Player::forward() {
	glm::vec3 dir = camera.getDirection();
	velocity.x = dir.x;
	velocity.z = dir.z;
}

void Player::backward() {
	glm::vec3 dir = -camera.getDirection();
	velocity.x = dir.x;
	velocity.z = dir.z;
}

void Player::strafeLeft() {
	glm::vec3 dir = -glm::normalize(glm::cross(camera.getDirection(), camera.getUp()));
	velocity.x = dir.x;
	velocity.z = dir.z;
}

void Player::strafeRight() {
	glm::vec3 dir = glm::normalize(glm::cross(camera.getDirection(), camera.getUp()));
	velocity.x = dir.x;
	velocity.z = dir.z;
}

void Player::jump() {
	if (grounded) {
		velocity.y = jumpSpeed;
	}
}

void Player::update(float deltaTime) {

	pos += velocity * deltaTime * speed;
	velocity -= glm::vec3(velocity * deltaTime * friction);

	if (pos.y < 0.001) {
		grounded = true;
		velocity.y = 0.0;
	}
	else {
		grounded = false;
		velocity.y -= gravity * deltaTime;
	}

	camera.setPos(pos + glm::vec3(0.0, height, 0.0));
	camera.look(*shader);
}