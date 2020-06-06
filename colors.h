
#ifndef CUBICRUBIK_COLORS_H
#define CUBICRUBIK_COLORS_H
#include "SFML/OpenGL.hpp"
enum class colors
{
    Red,
    Green,
    Blue,
    White,
    Magenta,
    Orange,
    Black
};
void setGlColor(colors color);
#endif
