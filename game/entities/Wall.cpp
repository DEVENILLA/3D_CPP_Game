#include "Wall.h"
#include "cmath"
#include "../Game.h"

void Wall::render()
{
    int topLeftX = (int)(getTopLeft(point1, point2).x);
    int topLeftY = (int)(getTopLeft(point1, point2).y);
    int width = (int)abs(point2.x-point1.x);
    int height = (int)abs(point2.y-point1.y);
    if (game->isBuildMode)
        DrawRectangleLines(topLeftX, topLeftY, width, height, WHITE);
    else
        DrawRectangle(topLeftX, topLeftY, width, height, WHITE);
}

bool Wall::isCollidingWith(Vector2 center, float radius)
{
    int topLeftX = (int)(getTopLeft(point1, point2).x);
    int topLeftY = (int)(getTopLeft(point1, point2).y);
    int width = (int)abs(point2.x-point1.x);
    int height = (int)abs(point2.y-point1.y);

    Rectangle rect;
    rect.x = topLeftX;
    rect.y = topLeftY;
    rect.width = width;
    rect.height = height;

    if (CheckCollisionCircleRec(center, radius, rect))
        return true;
    return false;
}
