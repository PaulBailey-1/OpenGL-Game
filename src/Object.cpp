#include "Object.h"

Object::Object(const char* path, Shader* shader_, glm::vec3 pos_) {

	model = nullptr;
	if (path != "") {
		model = new Model(path);
	}

	shader = shader_;
	modelMat = glm::mat4(1.0f);
	pos = pos_;

	scale = glm::vec3(0.1);
	rotate = glm::vec3(1.0);
}

void Object::setPos(glm::vec3 pos_) {
	pos = pos_;
}

void Object::setScale(glm::vec3 scale_) {
	scale = scale_;
}

void Object::setRotate(glm::vec3 rotate_) {
	rotate = rotate_;
}

void Object::draw() {

	modelMat = glm::scale(modelMat, scale);
	modelMat = glm::translate(modelMat, pos);

	shader->setMat4("model", modelMat);
	modelMat = glm::mat4(1.0f);

	if (model != nullptr) {
		model->draw(*shader);
	}
}