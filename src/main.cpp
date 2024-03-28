#include <random>
#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "Game.hpp"

int RandomNumber(const int min, const int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return (distribution(mt));
}

int main() {
    Game game;
    game.RunGame();

    return 0;
}