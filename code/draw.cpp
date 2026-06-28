#include "draw.h"
#include <math.h>
#include <string>
#include <vector>

void drawline(std::vector<std::vector<std::pair<char,
                                                char>>>& screen,
              int x1,
              int y1,
              int x2,
              int y2)
{
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx  = (x1 < x2) ? 1 : -1;
    int sy  = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        // draw only if inside screen
        if (y1 >= 0 && y1 < screen.size() && x1 >= 0 && x1 < screen[0].size())
        {
            screen[y1][x1].first  = '#';
            screen[y1][x1].second = '#';
        }

        if (x1 == x2 && y1 == y2)
        {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}