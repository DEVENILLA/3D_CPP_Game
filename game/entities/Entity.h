#ifndef INC_3D_GAME_IN_C_ENTITY_H
#define INC_3D_GAME_IN_C_ENTITY_H


#include "raylib.h"
#include "../CONSTS.h"

class Game;

class Entity
{
    bool started = false;

public:
    float x = centerWidth;
    float y = centerHeight;
    int size = 10;
    float rotation = 0;
    Game *game;

    Entity();
    ~Entity();

    void tick(float input[5])
    {
        if (started)
            update(input);
        else
        {
            start(input);
            started = true;
        }
    };

    virtual void start(float *input);

    virtual void update(float *input);

    virtual void render();

    void move_step(float step_x, float step_y, int _speed);
    bool is_in_wall();

    float get_rotation();
    void rotate(float amount);
    Vector2 get_forward_vector();
    Vector2 get_side_vector();
};

class Player : public Entity
{
public:
    float speed = 5;

    Player();
    ~Player();

    void update(float *input) override;

    void move(float front_step, float side_step);
};

#endif //INC_3D_GAME_IN_C_ENTITY_H
