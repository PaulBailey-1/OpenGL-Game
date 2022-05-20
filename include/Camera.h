#pragma once
#include <glm/glm.hpp>
#include <SFML/System.hpp>

#include "Shader.h"

class Camera {
public:

	Camera(int winWidth, int winHeight, glm::vec3 startingPos);

    void look(Shader& shader);
    sf::Vector2i updateMouse(sf::Vector2i mousePos);

    glm::vec3 getDirection() { return movement; }
    glm::vec3 getUp() { return cameraUp; }

    void setPos(glm::vec3 pos_) { cameraPos = pos_; }

private:

    int winWidth;
    int winHeight;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 movement;

    glm::mat4 view;
    glm::mat4 projection;

    int xpos;
    int ypos;

    float pitch;
    float yaw;

    bool firstMouse = true;
};

