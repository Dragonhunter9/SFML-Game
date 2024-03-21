#pragma once
#include "SFML/Graphics.hpp"

class Level {
private:
    unsigned int levelNumber;
    unsigned int requiredScore;
    float fallingSpeed;
    sf::Vector2i spawnSpeed;
    int bombPossibility;

public:
    Level();
    Level(const int& number, const int& score, const float& speed, const sf::Vector2i& spawningSpeed, const int& bombSpawnPossibility);

    int GetLevelNumber() const { return levelNumber; };
    unsigned int GetRequiredScore() const { return requiredScore; }
    float GetFallingSpeed() const { return fallingSpeed; }
    sf::Vector2i GetSpawnSpeed() const { return spawnSpeed; }
    int GetBombPossiblity() const { return bombPossibility; }
};