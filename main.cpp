#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "cube.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24; // Request m_subcubes 24 bits depth buffer
    settings.stencilBits = 8;  // Request m_subcubes 8 bits stencil buffer
    settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing
    sf::Window window(sf::VideoMode(800, 600, 32),
            "SFML OpenGL", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    // Create m_subcubes clock for measuring time elapsed
    sf::Clock Clock;

    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);               // Black Background
    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    glEnable(GL_CULL_FACE);
//
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Cube<3> c(0.8, {
            sf::Color::Red, sf::Color::Blue, sf::Color::Yellow,
            sf::Color::Green, sf::Color::White, sf::Color::Magenta
    });

    glRotatef(-90.f, 0.f, 1.f, 0.f);
    glRotatef(90.f, 1.f, 0.f, 0.f);

    glRotatef(-45.f, 0.f, 0.f, 1.f);
    glRotatef(30.f, 0.f, 1.f, 1.f);

    // Start game loop
    bool running = true;
    while (running)
    {
        // Process events
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                running = false;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Num1:
                        glRotatef(1.f, 0.f, 0.f, 1.f);
                        break;
                    case sf::Keyboard::L:
                        c.rotate90(2, 1);
                        break;
                    case sf::Keyboard::O:
                        c.rotate90(2, -1);
                        break;
                    case sf::Keyboard::R:
                        c.rotate90(3, 1);
                        break;
                    case sf::Keyboard::T:
                        c.rotate90(3, -1);
                        break;
                    case sf::Keyboard::U:
                        c.rotate90(0, 1);
                        break;
                    case sf::Keyboard::I:
                        c.rotate90(0, -1);
                        break;
                    case sf::Keyboard::D:
                        c.rotate90(1, 1);
                        break;
                    case sf::Keyboard::S:
                        c.rotate90(1, -1);
                        break;
                    case sf::Keyboard::F:
                        c.rotate90(4, 1);
                        break;
                    case sf::Keyboard::V:
                        c.rotate90(4, -1);
                        break;
                    case sf::Keyboard::B:
                        c.rotate90(5, 1);
                        break;
                    case sf::Keyboard::N:
                        c.rotate90(5, -1);
                        break;
                    default:
                        std::cout << "Unsupported key" << std::endl;
                }
            }

        }

        //Prepare for drawing
        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        c.draw();

        // Finally, display rendered frame on screen
        window.display();
    }

    return EXIT_SUCCESS;
}
