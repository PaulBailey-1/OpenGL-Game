#include "Object.h"

Object::Object(const char* path, Shader* shader_, glm::vec3 pos_) {

	model = nullptr;
	length = 0.0;
	width = 0.0;
	height = 0.0;

	if (path != "") {
		model = new Model(path);
		length = model->getLength();
		width = model->getWidth();
		height = model->getHeight();
	}

	shader = shader_;
	modelMat = glm::mat4(1.0f);
	pos = pos_;

	scale = glm::vec3(1.0);
	//rotate = glm::vec3(1.0);

	setScale(glm::vec3(0.1));
}

void Object::setPos(glm::vec3 pos_) {
	pos = pos_;
}

void Object::setScale(glm::vec3 scale_) {

	length *= scale_.x / scale.x;
	width *= scale_.z / scale.z;
	height *= scale_.y / scale.y;

	scale = scale_;
}

//void Object::setRotate(glm::vec3 rotate_) {
//	rotate = rotate_;
//}

void Object::draw() {

	modelMat = glm::scale(modelMat, scale);
	modelMat = glm::translate(modelMat, pos);

	shader->setMat4("model", modelMat);
	modelMat = glm::mat4(1.0f);

	if (model != nullptr) {
		model->draw(*shader);
	}
}

float Object::getPosX() {
	return pos.x - length / 2;
}

float Object::getPosY() {
	return pos.y - height / 2;
}

float Object::getPosZ() {
	return pos.z - width / 2;
}

bool Object::xIntersection(Object other) {

	float xL1 = getPosX();
	float xR1 = getPosX() + length;

	float xL2 = other.getPosX();
	float xR2 = other.getPosX() + other.length;

	return xL1 < xR2 && xR1 > xL2;
}

bool Object::yIntersection(Object other) {

	float yL1 = getPosY();
	float yR1 = getPosY() + height;

	float yL2 = other.getPosY();
	float yR2 = other.getPosY() + other.height;

	return yL1 < yR2 && yR1 > yL2;
}

bool Object::zIntersection(Object other) {

	float zL1 = getPosZ();
	float zR1 = getPosZ() + width;

	float zL2 = other.getPosZ();
	float zR2 = other.getPosZ() + other.width;

	return zL1 < zR2 && zR1 > zL2;
}