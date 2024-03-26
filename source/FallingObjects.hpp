#pragma once
#include "SFML/Graphics.hpp"

class FallingObject {
protected:
    sf::CircleShape object;

    void Move(const float deltaTime);

    bool TestIfDraw(const sf::RenderWindow& window);

public:
    enum ObjectType {
        FallingObj = 0, Coin, Bomb
    };

    virtual ObjectType GetType() const;

    FallingObject();

    static std::vector<std::unique_ptr<FallingObject>> objects;
    static float velocity;
    static sf::Clock timer;
    static float pauseTime;
    bool drawObject;

    virtual ~FallingObject() = default;

    static void DrawAllObjects(sf::RenderWindow& window);

    static void MoveAllObjects(const float deltaTime);

    static void AddPoints(const sf::RenderWindow& window, unsigned int points);

    sf::FloatRect GetGlobalBounds() const;
};

class Coin : public FallingObject {
public:
    Coin();

    ObjectType GetType() const override;
};

class Bomb : public FallingObject {
public:
    Bomb();

    Bomb(const float playerPos);

    ObjectType GetType() const override;
};