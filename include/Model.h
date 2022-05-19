#pragma once

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"

class Model {
public:

	Model(const char* path);

	void draw(Shader& shader);

	float getLength();
	float getWidth();
	float getHeight();

private:

	std::vector<Mesh> meshes;
	std::vector<Texture> textures_loaded;
	std::string directory;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int getTexture(const char* filename, const std::string& directory);

};
