
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "subcube.h"
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}
int main(){

    sf::Window App(sf::VideoMode(800, 600, 32), "SFML OpenGL");

    // Create a clock for measuring time elapsed
    sf::Clock Clock;

    //prepare OpenGL surface for HSR
    glClearDepth(1.f);
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar



    bool rotate=true;
    float angle;
    subcube test;
    test.setSize(50);
    test.setColor(0, colors::Red);
    test.setColor(1, colors::Magenta);
    test.setColor(2, colors::White);
    test.setColor(3, colors::Green);
    test.setColor(4, colors::Blue);
    test.setColor(5, colors::Orange);
    // Start game loop

    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();

            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                App.close();

            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A)){
                rotate=!rotate;
            }

        }

        //Prepare for drawing
        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply some transformations for the cube
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);

        if(rotate){
            angle=Clock.getElapsedTime().asSeconds();
        }
        glRotatef(angle * 50, 1.f, 0.f, 0.f);
//        glRotatef(angle * 30, 0.f, 1.f, 0.f);
//        glRotatef(angle * 90, 0.f, 0.f, 1.f);
        test.draw();

        // Finally, display rendered frame on screen
        App.display();
    }

    return EXIT_SUCCESS;
}