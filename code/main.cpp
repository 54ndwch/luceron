#include "main.h"
#include "render.h"
#include <conio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>

int main(int argc,
         char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    long long vx = -150, vy = -150, vw, vh, sw = 20, sh = 20;
    bool hidetext = false;
    if (1 < argc)
    {
        sw = atoi(argv[1]);
        sh = sw;
        if (2 < argc)
        {
            sh = atoi(argv[2]);
        }
        if (sw == 0 || sh == 0)
        {
            sw = 20;
            sh = 20;
        }
        else
        {
            std::cout << "Default screen width override sw sh: " << sw << ' ' << sh;
            vx += vw / 2;
            vw = sw * vh / sh;
            vx -= vw / 2;
        }
    }
    if (sw <= sh)
    {
        vw = 1250;
        vh = sh * vw / sw;
    }
    else
    {
        vh = 1250;
        vw = sw * vh / sh;
    }
    vx = -vw / 2;
    vy = -vh / 2;
    std::cout << "\033[2J";
    render(vx, vy, vw, vh, sw, sh, hidetext);
    renderoverlay({"move      [WASD]",
                   "set pos   [F]",
                   "zoom      [QE]",
                   "set zoom  [R]",
                   "get view  [G]",
                   "set view  [T]",
                   "hide text [H]"},
                  sw);
    while (true)
    {
        char ch = _getch();
        switch (ch)
        {
        case 'w':
        {
            if (vy <= LLONG_MIN + std::max(std::min(vh, vw) / 10, 1LL))
            {
                break;
            }
            vy -= std::max(std::min(vh, vw) / 10, 1LL);
            render(vx, vy, vw, vh, sw, sh, hidetext);
        }
        break;
        case 'a':
        {
            if (vx <= LLONG_MIN + std::max(std::min(vh, vw) / 10, 1LL))
            {
                break;
            }
            vx -= std::max(std::min(vh, vw) / 10, 1LL);
            render(vx, vy, vw, vh, sw, sh, hidetext);
        }
        break;
        case 's':
        {
            if (vy >= LLONG_MIN - std::max(std::min(vh, vw) / 10, 1LL))
            {
                break;
            }
            vy += std::max(std::min(vh, vw) / 10, 1LL);
            render(vx, vy, vw, vh, sw, sh, hidetext);
        }
        break;
        case 'd':
        {
            if (vx >= LLONG_MIN - std::max(std::min(vh, vw) / 10, 1LL))
            {
                break;
            }
            vx += std::max(std::min(vh, vw) / 10, 1LL);
            render(vx, vy, vw, vh, sw, sh, hidetext);
        }
        break;
        case 'q':
        {
            if (vh >= LLONG_MAX / 2)
            {
                break;
            }
            vx += vw / 2;
            vy += vh / 2;
            vh *= 2;
            vw *= 2;
            vx -= vw / 2;
            vy -= vh / 2;
            render(vx, vy, vw, vh, sw, sh, hidetext);
        }
        break;
        case 'e':
        {
            if (std::min(vw, vh) <= 1)
            {
                break;
            }
            vx += vw / 2;
            vy += vh / 2;
            vh /= 2;
            vw /= 2;
            vx -= vw / 2;
            vy -= vh / 2;
            render(vx, vy, vw, vh, sw, sh, hidetext);
        }
        break;
        case 'r':
        {
            clearinput(sw);
            long long cx = vx + vw / 2, cy = vy + vh / 2;
            std::cout << "r: ";
            if (sw <= sh)
            {
                std::cin >> vw;
                vw = abs(vw);
                vh = sh * vw / sw;
                vx = cx - vw / 2;
                vy = cy - vh / 2;
            }
            else
            {
                std::cin >> vh;
                vh = abs(vh);
                vw = sw * vh / sh;
                vx = cx - vw / 2;
                vy = cy - vh / 2;
            }
            render(vx, vy, vw, vh, sw, sh, hidetext);
        }
        break;
        case 'f':
        {
            clearinput(sw);
            long long cx, cy;
            std::cout << "cx cy: ";
            std::cin >> cx >> cy;
            vx = cx - vw / 2;
            vy = cy - vh / 2;
            render(vx, vy, vw, vh, sw, sh, hidetext);
        }
        break;
        case 't':
        {
            clearinput(sw);
            long long cx, cy;
            std::cout << "cx cy r: ";
            std::cin >> cx >> cy;
            if (sw <= sh)
            {
                std::cin >> vw;
                vh = sh * vw / sw;
            }
            else
            {
                std::cin >> vh;
                vw = sw * vh / sh;
            }
            vx = cx - vw / 2;
            vy = cy - vh / 2;
            render(vx, vy, vw, vh, sw, sh, hidetext);
        }
        break;
        case 'g':
        {
            clearinput(sw);
            std::cout << "cx cy r: " << vx + vw / 2 << ' ' << vy + vh / 2 << ' ' << std::min(vw, vh);
        }
        break;
        case 'h':
        {
            hidetext = !hidetext;
            render(vx, vy, vw, vh, sw, sh, hidetext);
        }
        break;
        case 27:
        {
            clearinput(sw);
            exit(0);
        }
        break;
        default:
        {
            clearinput(sw);
        }
        break;
        }
    }
    return 0;
}