#ifndef INC_3D_GAME_IN_C_CONSTS_H
#define INC_3D_GAME_IN_C_CONSTS_H
static const int screenWidth = 1200;
static const int screenHeight = 800;
static const int centerWidth = screenWidth/2;
static const int centerHeight = screenHeight/2;
static const int cellSize = 20;
static const int cellCount = screenWidth/cellSize * screenHeight/cellSize;

static Vector2 getTopLeft(Vector2 point1, Vector2 point2)
{
    float x = 0;
    float y = 0;
    x = point1.x <= point2.x ? point1.x : point2.x;
    y = point1.y <= point2.y ? point1.y : point2.y;
    return {x,y};
}
#endif //INC_3D_GAME_IN_C_CONSTS_H
