#ifndef CUBICRUBIK_SUBCUBE_H
#define CUBICRUBIK_SUBCUBE_H

#include <SFML/Graphics/Color.hpp>

class subcube
{
public:
    void draw();

    void draw(double x, double y, double z);

    void drawInCenter();

    void setColor(int index, sf::Color const& color);

    void setSize(double size);

    void rotateX();

    void rotateY();

    void rotateZ();

private:
    sf::Color m_colors[6]{};
    double m_size{0};

private:
    unsigned char _color[3]{};
    unsigned char* at(int i);
};

#endif
