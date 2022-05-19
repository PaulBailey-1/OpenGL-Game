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
#include "Object.h"
#include "Player.h"

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

    Player player(winWidth, winHeight, &shader, glm::vec3(0.0, 0.0, 3.0), 0.5);

    Object box("resources/models/cube/cube.obj", &shader, glm::vec3(0.0, 1.0, 0.0));
    Object ground("resources/models/ground/ground.obj", &shader);
    
    sf::Clock clock;

    bool escPressed = false;
    bool paused = false;

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                winWidth = event.size.width;
                winHeight = event.size.height;
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (!paused) {
            mousePos = player.updateMouse(mousePos);
            sf::Mouse::setPosition(mousePos, window);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.forward();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.backward();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.strafeLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.strafeRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player.jump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (!escPressed) {
                escPressed = true;
                if (!paused) {
                    window.setMouseCursorVisible(true);
                    window.setMouseCursorGrabbed(false);
                    paused = true;
                }
                else {
                    window.setMouseCursorVisible(false);
                    window.setMouseCursorGrabbed(true);
                    paused = false;
                    sf::Mouse::setPosition(sf::Vector2i(winWidth / 2, winHeight / 2), window);
                }
            }
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            escPressed = false;
        }

        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        player.update(deltaTime);

        // clear the buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
        shader.use();

        player.draw();

        ground.setScale(glm::vec3(100.0));
        ground.draw();

        box.draw();

        window.display();
    }

    return 0;
}