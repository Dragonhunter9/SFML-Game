#pragma once
#include "SFML/Graphics.hpp"
#include "Entity/Player.hpp"
#include "Level.hpp"
#include "GUI/Gui.hpp"

int RandomNumber(const int min, const int max);

class Game {
    enum GameState {
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
    int objectSpawnTime;

    //tgui::Gui gameGUI;
    owngui::GuiStyle guiStyle;
    std::map<std::string, owngui::Gui> guiSystem;

    void createLevels();

    void updateLevel();

    void nextLevel();

    void resetLevel();

    void loadGuiConfigs();

    void displayPauseScreen();

    void displayTGUIWonScreen();

    void displayWonScreen();

    void displayGameOverScreen();

    void DrawGame();

    void UpdateGame();

    void ProcessEventsAndInputs();

public:
    Game();

    void RunGame();
};