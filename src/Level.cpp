#include "Level.hpp"

// Constructors

Level::Level() : levelNumber(0), requiredScore(1), fallingSpeed(100.0f), spawnSpeed(sf::Vector2i(1, 4)), bombPossibility(4) {}

Level::Level(const int& number, const int& score, const float& speed, const sf::Vector2i& spawningSpeed, const int& bombSpawnPossibility)
    : levelNumber(number), requiredScore(score), fallingSpeed(speed), spawnSpeed(spawningSpeed), bombPossibility(bombSpawnPossibility) {}

// Class methods

int Level::GetLevelNumber() const { return levelNumber; };

unsigned int Level::GetRequiredScore() const { return requiredScore; }

float Level::GetFallingSpeed() const { return fallingSpeed; }

sf::Vector2i Level::GetSpawnSpeed() const { return spawnSpeed; }

int Level::GetBombPossiblity() const { return bombPossibility; }