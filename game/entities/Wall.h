#ifndef INC_3D_GAME_IN_C_WALL_H
#define INC_3D_GAME_IN_C_WALL_H


#include "raylib.h"

class Game;

class Wall
{
public:
    Game *game;
    Vector2 point1;
    Vector2 point2;

    Wall() = default;
    ~Wall() = default;

    void render();

    bool isCollidingWith(Vector2 center, float radius);
};


#endif //INC_3D_GAME_IN_C_WALL_H
