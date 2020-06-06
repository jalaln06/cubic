#include "colors.h"
void setGlColor(colors color){
    switch (color)
    {
        case colors::Red:
            glColor3f(1,0,0);
            break;
        case colors::Orange:
            glColor3i(255,165,0);
            break;
        case colors::Blue:
            glColor3i(0,0,255);
            break;
        case colors::Green:
            glColor3i(0,255,0);
            break;
        case colors::White:
            glColor3i(255,255,255);
            break;
        case colors::Magenta:
            glColor3i(229,0,255);
            break;
        case colors::Black:
            glColor3i(0,0,0);
            break;

    }
}
