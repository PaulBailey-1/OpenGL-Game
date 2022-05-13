#pragma once

#include <GL/glew.h>

#define TEXTURE_UNITS 1

class Texture {
public:

	Texture(const char* filename);

	void bind(int num = 0);

private:

	unsigned int id;

	static bool textureUnitCheck;

};

