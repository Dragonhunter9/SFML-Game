#pragma once
#include "SFML/Graphics.hpp"
#include "CustomFunctions.h"

#include "FallingObject.h"

class Player {
private:
    sf::CircleShape ball;
    float velocity;

public:
    unsigned int score = 0;
    unsigned char lives = 3;

    Player(const sf::RenderWindow& window);

    void Draw(sf::RenderWindow& window) const;

    void Move(const sf::RenderWindow& window, const float& deltaTime);

    void Collided();

    void ResetPosition(const sf::RenderWindow& window);

    void DrawLives(sf::RenderWindow& window) const;

    sf::Vector2f GetPosition();
};