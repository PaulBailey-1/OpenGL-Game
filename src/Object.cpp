#include "Object.h"

Object::Object(const char* path, Shader* shader_) : model(path) {

	shader = shader_;
}

void Object::draw() {

	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::scale(modelMat, glm::vec3(0.1));

	shader->setMat4("model", modelMat);

	model.draw(*shader);
}