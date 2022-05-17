#pragma once
#include <glm/glm.hpp>
#include <Shader.h>

class Camera {
public:
	Camera(int winWidth, int winHeight);

    void look(Shader& shader);
    sf::Vector2i updateMouse(sf::Vector2i mousePos);

    void setSpeed(float elapsedTime);

    void setEsc(bool esc_) { esc = esc_; }
    bool getEsc() { return esc; }

    void forward();
    void backward();
    void strafeLeft();
    void strafeRight();

private:

    int winWidth;
    int winHeight;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view;
    glm::mat4 projection;

    int xpos;
    int ypos;

    float pitch;
    float yaw;

    float cameraSpeed;

    bool firstMouse = true;
    bool esc = false;
};

