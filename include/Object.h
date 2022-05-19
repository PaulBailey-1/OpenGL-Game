#pragma once
#include <Model.h>

class Object {
public:

	Object() {}
	Object(const char* path, Shader* shader_, glm::vec3 pos_ = glm::vec3(0.0));

	void draw();

	void setPos(glm::vec3 translate_);
	void setScale(glm::vec3 scale_);
	void setRotate(glm::vec3 rotate_);

private:

	Model* model;
	Shader* shader;

	glm::mat4 modelMat;

	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 rotate;

	float length;
	float width;
	float height;
};

