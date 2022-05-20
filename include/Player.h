#pragma once

#include "Camera.h"
#include "Object.h"
#include "Shader.h"

const float friction = 15.0;
const float speed = 3.0;
const float jumpSpeed = 4.0;
const float gravity = 12.0;

class Player {
public:

	Player(int winWidth, int winHeight, Shader* shader_, glm::vec3 startingPos, float height_, const char* path = "");

	sf::Vector2i updateMouse(sf::Vector2i mousePos);

	void update(float deltaTime);
	void draw();

	void setObjects(std::vector<Object*> &objects_) { objects = &objects_; }

	void forward();
	void backward();
	void strafeLeft();
	void strafeRight();

	void jump();

private:

	Camera camera;
	Object object;

	Shader* shader;

	std::vector<Object*>* objects;

	glm::vec3 pos;
	glm::vec3 velocity;

	float height;

	bool grounded;

};

