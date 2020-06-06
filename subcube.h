
#ifndef CUBICRUBIK_SUBCUBE_H
#define CUBICRUBIK_SUBCUBE_H

#include "colors.h"

class subcube
{
private:
    colors m_colors[6];
    double m_size;
public:
    subcube();

    void draw();

    void draw(double x, double y, double z);

    void setColor(int index, colors color);

    void setSize(int size);

    void rotateX();

    void rotateY();

    void rotateZ();

};

#endif
