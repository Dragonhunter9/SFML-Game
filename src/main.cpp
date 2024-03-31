#include "Game.hpp"
#include "GameState/GameState_LevelMode.hpp"

int main() {
    Game game;

    game.pushState(new GameState_LevelMode(&game));
    game.gameloop();

    return 0;
}