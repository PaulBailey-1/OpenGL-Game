#include "Object.h"

Object::Object(const char* path, Shader* shader_, glm::vec3 pos_) {

	model = nullptr;
	if (path != "") {
		model = new Model(path);
	}

	shader = shader_;
	modelMat = glm::mat4(1.0f);
	pos = pos_;
}

void Object::translate(glm::vec3 trans) {
	modelMat = glm::translate(modelMat, trans);
}

void Object::scale(float scale) {
	modelMat = glm::scale(modelMat, glm::vec3(scale));
}

void Object::draw() {

	scale(0.1);
	translate(pos);

	shader->setMat4("model", modelMat);
	modelMat = glm::mat4(1.0f);

	if (model != nullptr) {
		model->draw(*shader);
	}
}