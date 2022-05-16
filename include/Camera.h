#pragma once
#include <glm/glm.hpp>
#include <Shader.h>

class Camera {
public:
	Camera(int winWidth, int winHeight);

    void look(Shader& shader);

private:

    int winWidth;
    int winHeight;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view;
    glm::mat4 projection;

    int xpos = 0;
    int ypos = 0;

    float pitch = 0.0;
    float yaw = -90.0;

    bool firstMouse = true;
    bool esc = false;
    bool escPressed = false;
};

