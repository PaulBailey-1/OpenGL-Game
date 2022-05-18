#pragma once
#include <Model.h>

class Object {
public:

	Object() {}
	Object(const char* path, Shader* shader_, glm::vec3 pos_ = glm::vec3(0.0));

	void draw();
	void translate(glm::vec3 trans);
	void scale(float scale);

private:

	Model* model;
	Shader* shader;

	glm::mat4 modelMat;

	glm::vec3 pos;
};

