#include "Player.h"

Player::Player(int winWidth, int winHeight, Shader* shader_, glm::vec3 startingPos, float height_, const char* path) : 
		camera(winWidth, winHeight, startingPos + glm::vec3(0.0, height_, 0.0)),
		object(path, shader_, startingPos) {

	objects = std::vector<Object*>();

	shader = shader_;
	pos = startingPos;
	velocity = glm::vec3(0.0, 0.0, 0.0);

	height = height_;

	grounded = true;

	object.length = 0.1;
	object.width = 0.1;
	object.height = 0.5;
}

void Player::addObject(Object* object) {
	objects.push_back(object);
	objectInt.push_back(Interferance());
}

sf::Vector2i Player::updateMouse(sf::Vector2i mousePos) {
	return camera.updateMouse(mousePos);
}

void Player::draw() {
	object.setPos(pos);
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

	bool objectGrounded = false;
	for (int i = 0; i < objects.size(); i++) {

		bool xInt = object.xIntersection(objects[i]);
		bool yInt = object.yIntersection(objects[i]);
		bool zInt = object.zIntersection(objects[i]);

		if (objectInt[i].xInt && objectInt[i].yInt && !objectInt[i].zInt && zInt && !((pos.z + velocity.z > (objects[i]->getPosZ() + objects[i]->width)) || (pos.z + velocity.z < objects[i]->getPosZ()))) {
			velocity.z = 0.0;
			zInt = false;
		}

		if (objectInt[i].zInt && objectInt[i].yInt && !objectInt[i].xInt && xInt && !((pos.x + velocity.x > (objects[i]->getPosX() + objects[i]->length)) || (pos.x + velocity.x < objects[i]->getPosX()))) {
			velocity.x = 0.0;
			xInt = false;
		}

		if (objectInt[i].zInt && objectInt[i].xInt && !objectInt[i].yInt && yInt && !((pos.y + velocity.y - 0.5 > (objects[i]->getPosY() + objects[i]->height)) || (pos.y + velocity.y + 0.5 < objects[i]->getPosY()))) {
			if (velocity.y <= 0.0) {
				objectGrounded = true;
			}
			velocity.y = 0.0;
			yInt = false;
		}

		objectInt[i].xInt = xInt;
		objectInt[i].yInt = yInt;
		objectInt[i].zInt = zInt;
	}

	pos += velocity * deltaTime * speed;
	velocity -= glm::vec3(velocity.x * deltaTime * friction, 0.0, velocity.z * deltaTime * friction);

	if (pos.y < 0.001 || objectGrounded) {
		grounded = true;
		velocity.y = 0.0;
	} else {
		grounded = false;
		velocity.y -= gravity * deltaTime;
	}

	camera.setPos(pos + glm::vec3(0.0, height, 0.0));
	camera.look(*shader);
}