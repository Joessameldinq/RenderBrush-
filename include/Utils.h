#ifndef UTILS_H
#define UTILS_H

typedef struct Point{
    int x;
    int y;
};
bool isButtonClicked(Point click, Point buttonCorner, int width, int height);
#endif