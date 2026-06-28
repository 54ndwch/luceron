#ifndef RENDER_H
#define RENDER_H
#include "draw.h"
#include <string>

void render(long long vx,
            long long vy,
            long long vw,
            long long vh,
            long long sw,
            long long sh,
            bool hidetext);

void renderoverlay(std::vector<std::string> multiline,
                   long long sw);

void clearinput(long long tw);

#endif  // !RENDER_H