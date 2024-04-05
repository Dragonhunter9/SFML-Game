#pragma once
#include <SFML/Graphics.hpp>
#include <map>

#include "GameState/GameState.hpp"
#include "GUI/Gui.hpp"
#include "Entity/Player.hpp"

class Level {
public:
    int levelNumber;
    int requiredScore;
    float fallingSpeed;
    sf::Vector2i spawnSpeed;
    int bombPossibility;

    Level();

    Level(const int number, const int score, const float speed, const sf::Vector2i spawningSpeed, const int bombSpawnPossibility);

    int GetLevelNumber() const;
    int GetRequiredScore() const;
    float GetFallingSpeed() const;
    sf::Vector2i GetSpawnSpeed() const;
    int GetBombPossiblity() const;
};

class GameState_LevelMode : public GameState
{
private:
    enum SessionState {
        Running = 0, Paused, Won, GameOver
    };

    Player player;
    sf::Text scoreDisplay;
    sf::Text levelDisplay;
    SessionState gameStatus;
    std::vector<Level> levels;
    int currentLevel;
    int objectSpawnTime;

	std::map<std::string, Gui> guiSystem;

    constexpr void createLevels();
    void updateLevel();
    void nextLevel();
    void resetLevel();

    void loadGUI();

    void displayPauseScreen();
    void displayTGUIWonScreen();
    void displayWonScreen();
    void displayGameOverScreen();

public:
	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

	GameState_LevelMode(Game* game);
};