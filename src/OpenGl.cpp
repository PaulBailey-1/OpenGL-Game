#include <iostream>
#include <fstream>

#include <SFML/Window.hpp>
#include <GL/glew.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"

int main()
{

    int winWidth = 1500;
    int winHeight = 1000;

    // create the window
    sf::Window window(sf::VideoMode(winWidth, winHeight), "OpenGL", sf::Style::Default, sf::ContextSettings(24, 8, 2, 3, 3));
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(false);

    sf::Mouse::setPosition(sf::Vector2i(winWidth / 2, winHeight / 2), window);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...

    glewInit();

    glEnable(GL_DEPTH_TEST);

    Shader shader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");

    Camera camera(winWidth, winHeight);

    Model octo("resources/models/cube/cube.obj");
    
    sf::Clock clock;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    int xpos = 0;
    int ypos = 0;

    float pitch = 0.0;
    float yaw = -90.0;

    bool firstMouse = true;
    bool esc = false;
    bool escPressed = false;

    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                winWidth = event.size.width;
                winHeight = event.size.height;
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        if (!esc) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Mouse::setPosition(sf::Vector2i(winWidth / 2, winHeight / 2), window);
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

        const float cameraSpeed = 3 * clock.getElapsedTime().asSeconds();
        clock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            cameraPos += cameraSpeed * cameraFront;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            cameraPos -= cameraSpeed * cameraFront;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (!escPressed) {
                escPressed = true;
                if (!esc) {
                    window.setMouseCursorVisible(true);
                    window.setMouseCursorGrabbed(false);
                    esc = true;
                }
                else {
                    window.setMouseCursorVisible(false);
                    window.setMouseCursorGrabbed(true);
                    esc = false;
                    sf::Mouse::setPosition(sf::Vector2i(winWidth / 2, winHeight / 2), window);
                }
            }
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            escPressed = false;
        }

        // clear the buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
        shader.use();

        camera.look(shader);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.1));

        shader.setMat4("model", model);

        octo.draw(shader);

        window.display();
    }

    return 0;
}