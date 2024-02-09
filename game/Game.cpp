#include "Game.h"
#include "raylib.h"
#include "cmath"

Game ::Game() = default;
Game ::~Game()= default;

int Game::init()
{
    InitWindow(screenWidth, screenHeight, "3D Game");
    SetTargetFPS(60);
    initGridCells();
    return 0;
}

void Game::initGridCells()
{
    int x = 0;
    int y = 0;
    for (auto & cell : cells)
    {
        cell.top_left.x = x;
        cell.top_left.y = y;

        if (x == screenWidth-cellSize && y == screenHeight-cellSize)
            break;
        else
        {
            if (x == screenWidth-cellSize)
                x = 0;
            else
                x += cellSize;

            if (y == screenHeight-cellSize)
                y = 0;
            else
                y += cellSize;
        }
    }
}

int Game::getCellIndex(Vector2 pos)
{
    int index = pos.y * screenWidth / cellSize + pos.x / cellSize;
    return index;
}

Vector2 Game::SnapToCell(Vector2 position)
{
    Vector2 snappedPosition;
    snappedPosition.x = ((int)round(position.x / cellSize)) * cellSize;
    snappedPosition.y = ((int)round(position.y / cellSize)) * cellSize;
    return snappedPosition;
}


void Game::start()
{
    auto* p = new Player();
    entities.push_front(p);
    tick_entities();
}

void Game::handle_input()
{
    // moving left or right
    input[0] = 0 + (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) - (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A));
    input[1] = 0 - (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) + (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S));

    Vector2 mousePos = GetMousePosition();
    mouse_vel_x = (mousePos.x - last_mouseX);
    mouse_vel_y = (mousePos.y - last_mouseY);
    last_mouseX = mousePos.x;
    last_mouseY = mousePos.y;

    input[2] = mouse_vel_x;
    input[3] = mouse_vel_y;
}

void Game::update()
{
    handle_build_mode();
    tick_entities();
}

void Game::tick_entities()
{
    for (auto & entity : entities)
    {
        entity->tick(input);
    }
}

void Game::handle_build_mode()
{
    if (IsKeyPressed(KEY_B))
    {
        isBuildMode = !isBuildMode;
        ApplyBuildChanges();
    }

    if (isBuildMode)
    {
        if (IsKeyPressed(KEY_Z) && IsKeyDown(KEY_LEFT_CONTROL) && walls.size() > 0)
            walls.pop_front();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int target = 0;
            switch (wall_build_turn)
            {
                case 0:
                    point1 = SnapToCell(GetMousePosition());
                    target = 1;
                    break;
                case 1:
                    point2 = SnapToCell(GetMousePosition());
                    Wall *new_wall = new Wall();
                    new_wall->point1 = point1;
                    new_wall->point2 = point2;
                    new_wall->game = this;
                    walls.push_front(new_wall);
                    target = 0;
                    break;
            }
            wall_build_turn = target;
        }
    }
    else
    {
        wall_build_turn = 0;
    }
}

void Game::ApplyBuildChanges()
{
    if (isBuildMode) return;
    if (walls.size() <= 0) return;
    for (Cell & cell : cells)
    {
        for (auto & wall : walls)
        {
            if (wall->isCollidingWith(cell.getCenter(), cellSize/2))
            {
                cell.isBlocked = true;
                break;
            }
        }
    }
}

bool Game::isThereCollision(Vector2 position, int radius)
{
    float topY = position.y - radius;
    float bottomY = position.y + radius;
    float leftX = position.x - radius;
    float rightX = position.x + radius;

    if (topY < 0 || leftX < 0 || rightX > screenWidth || bottomY > screenHeight)
        return true;

    return false;
}


void Game::render()
{
    /* screen is editable */
    BeginDrawing();
    /* screen is cleared*/
    ClearBackground(BLACK);

    /* do what you want here */
    for (auto & entity : entities)
    {
        entity->render();
    }
    for (auto & wall : walls)
    {
        wall->render();
    }
    if (isBuildMode)
    {
        DrawCircle(SnapToCell(GetMousePosition()).x, SnapToCell(GetMousePosition()).y, 5, RED);
        render_build_mode_box();
    }
    /* do what you want here */

    /* screen is un-editable */
    EndDrawing();
}

void Game::render_build_mode_box()
{
    if (wall_build_turn != 0)
    {
        int topLeftX = (int)(getTopLeft(point1, SnapToCell(GetMousePosition())).x);
        int topLeftY = (int)(getTopLeft(point1, SnapToCell(GetMousePosition())).y);
        int width = (int)abs(point1.x-SnapToCell(GetMousePosition()).x);
        int height = (int)abs(point1.y-SnapToCell(GetMousePosition()).y);
        DrawRectangleLines(topLeftX, topLeftY, width, height, WHITE);
    }
}


void Game::close()
{
    CloseWindow();
}

bool Game::running()
{
    return !WindowShouldClose();
}
