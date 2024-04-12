#include "Game.hpp"
#include "GameState/GameState_Start.hpp"

int main() {
    Game game;

    game.pushState(new GameState_Start(&game));
    game.gameloop();

    return 0;
}