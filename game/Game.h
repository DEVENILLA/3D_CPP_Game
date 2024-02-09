#ifndef INC_3D_GAME_IN_C_GAME_H
#define INC_3D_GAME_IN_C_GAME_H

#include <list>
#include "entities/Entity.h"
#include "entities/Wall.h"
#include "iostream"
#include "raylib.h"
#include "CONSTS.h"

using namespace std;

class Cell
{
public:
    Vector2 top_left;
    bool isBlocked = false;

    Vector2 getCenter()
    {
        return {top_left.x+cellSize/2, top_left.y+cellSize/2};
    };

    Cell() = default;
    ~Cell() = default;
};

class Game
{
    int last_mouseX = 0;
    int last_mouseY = 0;
    int mouse_vel_x = 0;
    int mouse_vel_y = 0;

public:

    /* INPUT HANDLING */
    /* { LEFT/RIGHT , UP/DOWN , MOUSE_X , MOUSE_Y , WEAPON_INPUT } */
    float input[5] = { 0, 0, 0, 0, 0 };
    /* ENTITIES */
    list<Entity*> entities = {};
    /* level blocks */
    Cell cells[cellCount];
    /* build mode */
    bool isBuildMode;
    int wall_build_turn = 0;
    Vector2 point1;
    Vector2 point2;
    list<Wall*> walls = {};

    Game();
    ~Game();

    int init();
    void start();

    void initGridCells();
    int getCellIndex(Vector2 pos);
    Vector2 SnapToCell(Vector2 position);


    void handle_input();
    void tick_entities();
    void update();
    void render();

    void handle_build_mode();

    bool isThereCollision(Vector2 position, int radius);

    void close();
    bool running();

    void render_build_mode_box();

    void ApplyBuildChanges();
};


#endif //INC_3D_GAME_IN_C_GAME_H
