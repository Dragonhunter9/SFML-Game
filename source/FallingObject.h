#pragma once
#include "SFML/Graphics.hpp"

class FallingObject {
protected:
    sf::CircleShape object;

    void Move(const float& deltaTime);

    bool TestIfDraw(const sf::RenderWindow& window);

public:
    enum ObjectType : unsigned char {
        FallingObj = 0, Coin, Bomb
    };

    virtual ObjectType GetType() const { return ObjectType::FallingObj; }

    FallingObject();

    static std::vector<std::unique_ptr<FallingObject>> objects;
    static float velocity;
    static sf::Clock timer;
    static float pauseTime;
    bool drawObject;

    virtual ~FallingObject() = default;

    static void DrawAllObjects(sf::RenderWindow& window);

    static void MoveAllObjects(const float& deltaTime);

    static void AddPoints(const sf::RenderWindow& window, unsigned int& points);

    sf::FloatRect GetGlobalBounds() const;
};