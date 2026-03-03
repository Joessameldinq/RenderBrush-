#include "../include/Utils.h"
bool isButtonClicked(Point click, Point buttonCorner, int width, int height) {
    return click.x >= buttonCorner.x &&
           click.x <= buttonCorner.x + width &&
           click.y >= buttonCorner.y &&
           click.y <= buttonCorner.y + height;
}