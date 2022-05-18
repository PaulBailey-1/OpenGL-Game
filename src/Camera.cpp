
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Camera.h"

Camera::Camera(int winWidth_, int winHeight_, glm::vec3 startingPos) {

    winWidth = winWidth_;
    winHeight = winHeight_;

    cameraPos = startingPos;
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    movement = glm::vec3(cameraFront.x, 0.0f, cameraFront.z);

    view = glm::mat4(1.0);
    projection = glm::perspective(glm::radians(45.0f), (float)winWidth / winHeight, 0.1f, 100.0f);

    xpos = 0;
    ypos = 0;

    pitch = 0.0;
    yaw = -90.0;

    firstMouse = true;

}

void Camera::look(Shader& shader) {

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

sf::Vector2i Camera::updateMouse(sf::Vector2i mousePos) {

    sf::Vector2i setMouse = mousePos;
    setMouse = sf::Vector2i(winWidth / 2, winHeight / 2);
    xpos = mousePos.x;
    ypos = mousePos.y;

    float xoffset = xpos - (winWidth / 2);
    float yoffset = (winHeight / 2) - ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
    movement = glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z));

    return setMouse;
}
