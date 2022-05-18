#pragma once
#include <Model.h>

class Object {
public:
	Object(const char* path, Shader* shader_);

	void draw();

private:

	Model model;
	Shader* shader;
};

