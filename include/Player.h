#pragma once

#include "Camera.h"
#include "Object.h"

class Player {
public:

	Player(int winWidth, int winHeight);

	sf::Vector2i updateMouse(sf::Vector2i mousePos);

	void setElapsedTime(float deltaTime);

	void forward();
	void backward();
	void strafeLeft();
	void strafeRight();

private:

	Camera camera;
	Object object;

};

