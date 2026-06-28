#include "render.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void render(long long vx,
            long long vy,
            long long vw,
            long long vh,
            long long sw,
            long long sh,
            bool hidetext)
{
    std::ifstream f("map.txt");
    if (!f.is_open())
    {
        std::cerr << "Failed to open\n";
    }
    std::vector<std::vector<std::pair<char, char>>> screen(sh, std::vector<std::pair<char, char>>(sw));
    for (std::vector<std::vector<std::pair<char, char>>>::iterator screenit = screen.begin(); screenit != screen.end(); screenit++)
    {
        for (std::vector<std::pair<char, char>>::iterator lineit = screenit->begin(); lineit!=screenit->end(); lineit++)
        {
            lineit->first = ' ';
            lineit->second = ' ';
        }
    }
    int x1, y1, x2, y2;
    std::string text;
    while (f >> std::ws && !f.eof())
    {
        if (f.peek() != '#')  //('0' <= f.peek() && f.peek() <= '9' || f.peek() == '-')
        {
            f >> x1 >> y1 >> x2 >> y2;
            x1 = (x1 - vx) * sw / vw;
            y1 = (y1 - vy) * sh / vh;
            x2 = (x2 - vx) * sw / vw;
            y2 = (y2 - vy) * sh / vh;
            drawline(screen, x1, y1, x2, y2);
        }
        else
        {
            f.ignore(1);
            std::getline(f, text);
            if (text[0] != '#')
            {
                f >> x1 >> y1;
                if (!hidetext)
                {
                    for (int i = 0; i < text.length(); i += 2)
                    {
                        int y = (y1 - vy) * sh / vh, x = (x1 - vx) * sw / vw;
                        if (0 <= y && y < screen.size() && 0 <= x + i / 2 && x + i / 2 < screen[0].size())
                        {
                            screen[y][x + i / 2].first  = text[i];
                            if (i+1 == text.length())
                            {
                                break;
                            }
                            screen[y][x + i / 2].second = text[i + 1];
                        }
                    }
                }
            }
        }
    }
    std::cout << "\033[H┌";
    for (int i = 0; i < sw * 2; i++)
    {
        std::cout << "─";
    }
    std::cout << "┐\n";
    for (std::vector<std::pair<char, char>> line : screen)
    {
        int textlen = 0;
        std::cout << "│";
        for (std::pair<char, char> p : line)
        {
            std::cout << p.first << p.second;
        }
        std::cout << "│\n";
    }
    std::cout << "┢";
    for (int i = 0; i < sw * 2; i++)
    {
        std::cout << "━";
    }
    std::cout << "┪\n";
    std::cout << "┃";
    for (int i = 0; i < sw * 2; i++)
    {
        std::cout << " ";
    }
    std::cout << "┃\n";
    std::cout << "┗";
    for (int i = 0; i < sw * 2; i++)
    {
        std::cout << "━";
    }
    std::cout << "┛\033[3G\033[A";
}

void renderoverlay(std::vector<std::string> multiline,
                   long long sw)
{
    long long ow = std::max_element(multiline.begin(),
                                    multiline.end(),
                                    [](std::string a, std::string b) { return a.length() < b.length(); })
                       ->length();
    std::cout << "\033[" << 3 + multiline.size() << "A╔═";
    for (int i = 0; i < ow; i++)
    {
        std::cout << "═";
    }
    std::cout << "═╗\n\033[2C";
    for (std::string s : multiline)
    {
        std::cout << "║ " << s << " ";
        for (int i = s.length(); i < ow; i++)
        {
            std::cout << " ";
        }
        std::cout << "║\n\033[2C";
    }
    std::cout << "╚═";
    for (int i = 0; i < ow; i++)
    {
        std::cout << "═";
    }
    std::cout << "═╝\n\n\033[3G";
}

void clearinput(long long sw)
{
    std::cout << "\033[3G";
    for (int i = 2; i < sw * 2; i++)
    {
        std::cout << " ";
    }
    std::cout << "\033[3G";
}