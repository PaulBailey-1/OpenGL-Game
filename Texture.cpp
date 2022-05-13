#include "Texture.h"

#include <string>
#include <stdio.h>
#include "stb_image.h"

bool Texture::textureUnitCheck = false;

Texture::Texture(const char* filename) {

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

    std::string filenameS = std::string(filename);
    std::string type = filenameS.substr(filenameS.find(".") + 1);

    if (data)
    {
        if (type == "jpg") {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if (type == "png") {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else
    {
        printf("Failed to load texture");
    }

    stbi_image_free(data);

    if (!textureUnitCheck) {
        int num;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &num);
        if (num < TEXTURE_UNITS) {
            printf("Error: invalid value for TEXTURE_UNITS - %i", TEXTURE_UNITS);
        }
        textureUnitCheck = true;
    }
}

void Texture::bind(int num) {
    if (num > TEXTURE_UNITS) {
        printf("Error: exceeded texture limit: num - %i limit - %i", num, TEXTURE_UNITS);
        return;
    }
    glActiveTexture(GL_TEXTURE0 + num);
    glBindTexture(GL_TEXTURE_2D, id);
}