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

    int GetLevelNumber() const;
    unsigned int GetRequiredScore() const;
    float GetFallingSpeed() const;
    sf::Vector2i GetSpawnSpeed() const;
    int GetBombPossiblity() const;
};