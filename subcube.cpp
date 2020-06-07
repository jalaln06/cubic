#include "subcube.h"
#include <SFML/OpenGL.hpp>

void subcube::draw()
{
    glPushMatrix();
    glBegin(GL_QUADS);

    // верх
    glColor3ubv(at(0));
    glNormal3f(0, 0, 1);
    glVertex3f(m_size, m_size, m_size);
    glVertex3f(0, m_size, m_size);
    glVertex3f(0, 0, m_size);
    glVertex3f(m_size, 0, m_size);

    // низ
    glColor3ubv(at(1));
    glNormal3f(0, 0, -1);
    glVertex3f(m_size, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, m_size, 0);
    glVertex3f(m_size, m_size, 0);

    // спереди
    glColor3ubv(at(2));
    glNormal3f(0, -1, 0);
    glVertex3f(m_size, 0, m_size);
    glVertex3f(0, 0, m_size);
    glVertex3f(0, 0, 0);
    glVertex3f(m_size, 0, 0);

    // сзади
    glColor3ubv(at(3));
    glNormal3f(0, 1, 0);
    glVertex3f(m_size, m_size, 0);
    glVertex3f(0, m_size, 0);
    glVertex3f(0, m_size, m_size);
    glVertex3f(m_size, m_size, m_size);

    // слева
    glColor3ubv(at(4));
    glNormal3f(-1, 0, 0);
    glVertex3f(0, m_size, m_size);
    glVertex3f(0, m_size, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, m_size);

    // справа
    glColor3ubv(at(5));
    glNormal3f(1, 0, 0);
    glVertex3f(m_size, m_size, 0);
    glVertex3f(m_size, m_size, m_size);
    glVertex3f(m_size, 0, m_size);
    glVertex3f(m_size, 0, 0);

    glEnd();
    glPopMatrix();
}

void subcube::setColor(int index, sf::Color const& color)
{
    m_colors[index] = color;
}

void subcube::setSize(double size)
{
    m_size = size;
}

void subcube::rotateX()
{
    sf::Color tmp = m_colors[0];
    m_colors[0] = m_colors[4];
    m_colors[4] = m_colors[1];
    m_colors[1] = m_colors[5];
    m_colors[5] = tmp;
}

void subcube::rotateY()
{
    sf::Color tmp = m_colors[2];
    m_colors[2] = m_colors[1];
    m_colors[1] = m_colors[3];
    m_colors[3] = m_colors[0];
    m_colors[0] = tmp;
}

void subcube::rotateZ()
{
    sf::Color tmp = m_colors[5];
    m_colors[5] = m_colors[3];
    m_colors[3] = m_colors[4];
    m_colors[4] = m_colors[2];
    m_colors[2] = tmp;
}

void subcube::draw(double x, double y, double z)
{
    glPushMatrix();
    glTranslated(x, y, z);
    draw();
    glPopMatrix();
}

void subcube::drawInCenter()
{
    double const offset = -m_size / 2.0;
    draw(offset, offset, offset);
}

unsigned char* subcube::at(int i)
{
    _color[0] = m_colors[i].r;
    _color[1] = m_colors[i].g;
    _color[2] = m_colors[i].b;
    return _color;
}
