#include "Entity.h"
#include "raylib.h"
#include "iostream"
#include "cmath"

using namespace std;

Player::Player()= default;
Player::~Player()= default;

void Player::update(float *input)
{
    move(input[1], input[0]);

    rotate(input[2]);
}

void Player::move(float front_step, float side_step)
{
    float stepX = get_forward_vector().x*front_step + get_side_vector().x*side_step;
    float stepY = get_forward_vector().y*front_step + get_side_vector().y*side_step;
    stepX *= -1;
    stepY *= -1;
    float normalizer = sqrt(pow(stepX,2)+pow(stepY,2));
    if (normalizer <= 0) normalizer = 1;
    stepX = stepX / normalizer;
    stepY = stepY / normalizer;

    move_step(stepX, stepY, speed);
}