#pragma once
#include "SFML/Graphics.hpp"
#include "FallingObjects.hpp"

class Player : public sf::Drawable {
private:
    sf::CircleShape ball;
    float velocity;

public:
    int score = 0;
    char lives = 3;

    Player(const sf::RenderWindow& window);

    void Move(const sf::RenderWindow& window, const float deltaTime);

    void Collided();

    void ResetPosition(const sf::RenderWindow& window);

    void DrawLives(sf::RenderWindow& window) const;

    sf::Vector2f GetPosition() const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};