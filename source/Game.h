#pragma once
#include "SFML/Graphics.hpp"
#include "CustomFunctions.h"

#include "Button.h"
#include "Player.h"
#include "Level.h"

#include "FallingObject.h"
#include "Bomb.h"
#include "Coin.h"

class Game {
    enum GameState : unsigned char {
        Running = 0, Paused, Won, GameOver
    };

    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window;
    Player player;
    sf::Text scoreDisplay;
    sf::Text levelDisplay;
    sf::Font font;
    sf::Clock deltaTimeClock;
    GameState gameStatus;
    std::vector<Level> levels;
    unsigned int currentLevel;
    int coinSpawnTime;

    void CreateLevels();

    void UpdateLevel();

    void ResetLevel();

    void DisplayPauseScreen();

    void DisplayWonScreen();

    void DisplayGameOverScreen();

    void DrawGame();

    void UpdateGame();

    void ProcessEventsAndInputs();

public:
    Game();

    void RunGame();
};