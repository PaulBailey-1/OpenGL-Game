
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Camera.h"

Camera::Camera(int winWidth_, int winHeight_) {

    winWidth = winWidth_;
    winHeight = winHeight_;

    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    view = glm::mat4(1.0);
    projection = glm::perspective(glm::radians(45.0f), (float)winWidth / winHeight, 0.1f, 100.0f);

    xpos = 0;
    ypos = 0;

    pitch = 0.0;
    yaw = -90.0;

    cameraSpeed = 0.0;

    firstMouse = true;
    esc = false;

}

void Camera::look(Shader& shader) {

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

sf::Vector2i Camera::updateMouse(sf::Vector2i mousePos) {

    sf::Vector2i setMouse = mousePos;
    if (!esc) {
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
    }

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    return setMouse;
}

void Camera::setSpeed(float elapsedTime) {
    cameraSpeed = 3000 * elapsedTime;
}

void Camera::forward() {
    cameraPos += cameraSpeed * cameraFront;
}

void Camera::backward() {
    cameraPos -= cameraSpeed * cameraFront;
}

void Camera::strafeLeft() {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::strafeRight() {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}