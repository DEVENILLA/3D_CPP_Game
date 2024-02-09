#include <iostream>
#include "game/Game.h"

using namespace std;

int main () {
    Game *game = new Game();
    if (game->init() != 0)
    {
        cout << "Game Failed to initialize" << endl;
        return 0;
    }

    game->start();
    while (game->running())
    {
        game->handle_input();
        game->update();
        game->render();
    }

    game->close();

    return 0;
}
