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