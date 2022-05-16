#include "Camera.h"

Camera::Camera(int winWidth_, int winHeight_) {

    winWidth = winWidth_;
    winHeight = winHeight_;

    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    view = glm::mat4(1.0);
    projection = glm::mat4(1.0);

    xpos = 0;
    ypos = 0;

    pitch = 0.0;
    yaw = -90.0;

    firstMouse = true;
    esc = false;
    escPressed = false;

}

void Camera::look(Shader& shader) {

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    projection = glm::perspective(glm::radians(45.0f), (float) winWidth / winHeight, 0.1f, 100.0f);

    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}