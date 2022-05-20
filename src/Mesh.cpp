#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices_, std::vector<unsigned int> indices_, std::vector<Texture> textures_) {

	vertices = vertices_;
	indices = indices_;
	textures = textures_;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texPos));

    glBindVertexArray(0);
}

void Mesh::draw(Shader& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.setFloat((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

float Mesh::getLength() {

    float most = 0.0;
    float least = 0.0;
    for (int i = 0; i < vertices.size(); i++) {
        float coord = vertices[i].position.x;
        if (coord > most) {
            most = coord;
        }
        if (coord < least) {
            least = coord;
        }
    }

    return most + abs(least);
}

float Mesh::getWidth() {

    float most = 0.0;
    float least = 0.0;
    for (int i = 0; i < vertices.size(); i++) {
        float coord = vertices[i].position.z;
        if (coord > most) {
            most = coord;
        }
        if (coord < least) {
            least = coord;
        }
    }

    return most + abs(least);
}

float Mesh::getHeight() {

    float most = 0.0;
    float least = 0.0;
    for (int i = 0; i < vertices.size(); i++) {
        float coord = vertices[i].position.y;
        if (coord > most) {
            most = coord;
        }
        if (coord < least) {
            least = coord;
        }
    }

    return most + abs(least);
}