#pragma once
#include <Model.h>

class Object {
public:

	Object(const char* path, Shader* shader_, glm::vec3 pos_ = glm::vec3(0.0));

	void draw();

	bool xIntersection(Object* other);
	bool yIntersection(Object* other);
	bool zIntersection(Object* other);

	void setPos(glm::vec3 translate_);
	void setScale(glm::vec3 scale_);
	//void setRotate(glm::vec3 rotate_);

	float getPosX();
	float getPosY();
	float getPosZ();

	float length;
	float width;
	float height;

private:

	Model* model;
	Shader* shader;

	glm::mat4 modelMat;

	glm::vec3 pos;
	glm::vec3 scale;
	//glm::vec3 rotate;

};

