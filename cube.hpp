#ifndef CUBICRUBIK_CUBE_H
#define CUBICRUBIK_CUBE_H

#include "subcube.h"
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <SFML/OpenGL.hpp>

template<unsigned N = 3>
class Cube
{
private:
    // 27 частей: [лево-право][перед-зад][низ-верх]
    subcube m_subcubes[N][N][N];

    // вспомогательные для вращения
    subcube m_tmp[N][N];

    // храним угол поворота каждой грани
    int m_rotate[6];

    // размер кубика-рубика
    double m_size;

    // цвета граней
    sf::Color m_colors[6];


public:
    Cube(double size, std::vector<sf::Color> const& colors)
    {
        clear(size, colors);
    }

    void clear(double size, std::vector<sf::Color> const& colors)
    {
        std::fill(m_rotate, m_rotate + 6, 0);
        m_size = size;

        if (colors.size() != 6)
        {
            throw std::runtime_error("Need 6 colors!");
        }
        std::copy(std::begin(colors), std::end(colors), std::begin(m_colors));

        // верх
        for (auto& i : m_subcubes)
        {
            for (auto& j : i)
            {
                j[N - 1].setColor(0, colors[0]);
            }
        }

        // низ
        for (auto& i : m_subcubes)
        {
            for (auto& j : i)
            {
                j[0].setColor(1, colors[1]);
            }
        }

        // спереди
        for (int k = 0; k < N; k++)
        {
            for (auto& m_subcube : m_subcubes)
            {
                m_subcube[0][k].setColor(2, colors[2]);
            }
        }

        // сзади
        for (int k = 0; k < N; k++)
        {
            for (auto& m_subcube : m_subcubes)
            {
                m_subcube[N - 1][k].setColor(3, colors[3]);
            }
        }

        // слева
        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < N; k++)
            {
                m_subcubes[0][k][i].setColor(4, colors[4]);
            }
        }

        // справа
        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < N; k++)
            {
                m_subcubes[N - 1][k][i].setColor(5, colors[5]);
            }
        }

        // устанавливаем размеры мелких деталей
        // это будет треть всего размера, умноженная на коэффициент немного меньший еденицы
        // (чтобы детали не были слишком плотно)
        double const subcubeSize = m_size / N * 0.95;
        for (auto& m_subcube : m_subcubes)
        {
            for (auto& j : m_subcube)
            {
                for (auto& k : j)
                {
                    k.setSize(subcubeSize);
                }
            }
        }
    }

    void draw()
    {
        double const baseShift = m_size / N;
        int const n2 = N / 2;

        for (int i = 0; i < N; i++)
        {
            double iShift = baseShift * (i - n2);
            for (int j = 0; j < N; j++)
            {
                double jShift = baseShift * (j - n2);
                for (int k = 0; k < N; k++)
                {
                    m_subcubes[i][j][k].draw(iShift, jShift, baseShift * (k - n2));
                }
            }
        }
    }

    void rotate90(int idx, int sign)
    {
        // sign задаётся в зависимости он направления
        // sign = -1, sign = 1
        // если sign = -1, значит крутим 3 раза
        if (sign == -1)
        {
            sign = 3;
        }
        while (sign--)
        {
            if (idx == 0 || idx == 1)
            {
                // низ/верх
                int k = (idx & 1) * (N - 1);
                // копируем повёрнутую на 90 градусов верхнюю/нижнюю грань
                // в массив m_tmp, затем грани присваиваем m_tmp
                // и не забываем повернуть каждую деталь этой грани
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        m_tmp[j][N - 1 - i] = m_subcubes[i][j][k];
                    }
                }
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        m_tmp[i][j].rotateZ();
                        m_subcubes[i][j][k] = m_tmp[i][j];
                    }
                }
            }
            else if (idx == 2 || idx == 3)
            {
                // лево/право
                int j = (idx & 1) * (N - 1);
                for (int i = 0; i < N; i++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        m_tmp[k][N - 1 - i] = m_subcubes[i][j][k];
                    }
                }
                for (int i = 0; i < N; i++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        m_tmp[i][k].rotateX();
                        m_subcubes[i][j][k] = m_tmp[i][k];
                    }
                }
            }
            else if (idx == 4 || idx == 5)
            {
                // впереди/сзади
                int i = (idx & 1) * (N - 1);
                for (int j = 0; j < N; j++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        m_tmp[k][N - 1 - j] = m_subcubes[i][j][k];
                    }
                }
                for (int j = 0; j < N; j++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        m_tmp[j][k].rotateY();
                        m_subcubes[i][j][k] = m_tmp[j][k];
                    }
                }
            }
        }
    }
};

#endif //CUBICRUBIK_CUBE_H
