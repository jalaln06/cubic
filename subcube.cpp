
#include "subcube.h"
#include <algorithm>

void subcube::draw()
{
    glPushMatrix();
    glBegin(GL_QUADS);//draw some squares
    // upper cap
    setGlColor(m_colors[0]);
    glColor3f(1,0,0);
    glNormal3f(0, 0, 1);
    glVertex3f(m_size, m_size, m_size);
    glVertex3f(0, m_size, m_size);
    glVertex3f(0, 0, m_size);
    glVertex3f(m_size, 0, m_size);
    // bottom cap
    setGlColor(m_colors[1]);
    glColor3f(0,1,0);
    glNormal3f(0, 0, -1);
    glVertex3f(m_size, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, m_size, 0);
    glVertex3f(m_size, m_size, 0);
    // front cap
    setGlColor(m_colors[2]);
    glColor3f(0,0,1);
    glNormal3f(0, -1, 0);
    glVertex3f(m_size, 0, m_size);
    glVertex3f(0, 0, m_size);
    glVertex3f(0, 0, 0);
    glVertex3f(m_size, 0, 0);
    // back cap
    setGlColor(m_colors[3]);
    glNormal3f(0, 1, 0);
    glVertex3f(m_size, m_size, 0);
    glVertex3f(0, m_size, 0);
    glVertex3f(0, m_size, m_size);
    glVertex3f(m_size, m_size, m_size);
    // left cap
    setGlColor(m_colors[4]);
    glNormal3f(-1, 0, 0);
    glVertex3f(0, m_size, m_size);
    glVertex3f(0, m_size, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, m_size);
    // right cap
    setGlColor(m_colors[5]);
    glNormal3f(1, 0, 0);
    glVertex3f(m_size, m_size, 0);
    glVertex3f(m_size, m_size, m_size);
    glVertex3f(m_size, 0, m_size);
    glVertex3f(m_size, 0, 0);
    glEnd();
    glPopMatrix();
}

void subcube::setColor(int index, colors color)
{
    m_colors[index] = color;
}

void subcube::setSize(int size)
{
    m_size = size;
}

void subcube::rotateX()
{
    colors tmp = m_colors[0];
    m_colors[0] = m_colors[4];
    m_colors[4] = m_colors[1];
    m_colors[1] = m_colors[5];
    m_colors[5] = tmp;
}

void subcube::rotateY()
{
    colors tmp = m_colors[2];
    m_colors[2] = m_colors[1];
    m_colors[1] = m_colors[3];
    m_colors[3] = m_colors[0];
    m_colors[0] = tmp;
}

void subcube::rotateZ()
{
    colors tmp = m_colors[5];
    m_colors[5] = m_colors[3];
    m_colors[3] = m_colors[4];
    m_colors[4] = m_colors[2];
    m_colors[2] = tmp;
}

subcube::subcube() : m_size{0}
{
    std::fill(m_colors, m_colors + 6, colors::Blue);
}

void subcube::draw(double x, double y, double z)
{
    glPushMatrix();
    glTranslated(x, y, z);
    draw();
    glPopMatrix();
}
