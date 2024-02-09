#include "Entity.h"
#include "../Game.h"
#include "cmath"

Entity::Entity()= default;
Entity::~Entity()= default;


void Entity::start(float *input)
{

}

void Entity::update(float *input)
{

}


void Entity::move_step(float step_x, float step_y, int _speed)
{
    for (int i = 0; i < _speed; i++)
    {
        x += step_x;
        if (is_in_wall())
        {
            x -= step_x;
        }
        y += step_y;
        if (is_in_wall())
        {
            y -= step_y;
        }
    }
}

bool Entity::is_in_wall()
{
    if (game->isThereCollision({x, y}, size))
    {
        return true;
    }
    return false;
}


void Entity::render()
{
    /* 2D Rendering */
    DrawCircle(x,y,size, WHITE);
    float distanceX = x+(size*1.8*get_forward_vector().x);
    float distanceY = y+(size*1.8*get_forward_vector().y);
    DrawLineEx({x,y}, {distanceX,distanceY}, size*.3, RED);
    distanceX = x+(size*1.5*get_side_vector().x);
    distanceY = y+(size*1.5*get_side_vector().y);
    DrawLineEx({x,y}, {distanceX,distanceY}, size*.3, GREEN);
}

float Entity::get_rotation()
{
    if (rotation > 360) rotation = 0;
    if (rotation < 0) rotation = 360;
    return rotation;
}

void Entity::rotate(float amount)
{
    rotation += amount;
    if (rotation > 360) rotation = 0;
    if (rotation < 0) rotation = 360;
}

Vector2 Entity::get_forward_vector() {
    Vector2 vector = {0,0};
    float rot = (get_rotation()) * PI / 180;
    vector.x = cos(rot);
    vector.y = sin(rot);
    return vector;
}

Vector2 Entity::get_side_vector() {
    Vector2 vector = {0,0};
    float rot = (get_rotation()-90) * PI / 180;
    vector.x = cos(rot);
    vector.y = sin(rot);
    return vector;
}
