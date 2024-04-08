#pragma once
#include "SFML/Graphics.hpp"

struct ObjectContainer;

class FallingObject {
protected:
    int radius;
    sf::CircleShape object;

    bool TestIfDraw(const sf::RenderWindow& window);

public:
    enum ObjectType {
        FallingObj = 0, Coin, Bomb
    };

    void Move(const float deltaTime);
    void Draw(sf::RenderWindow& window) const;

    virtual ObjectType GetType() const;

    FallingObject();

    static ObjectContainer objectsContainer;
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
    static sf::Texture* tex;

    Coin();

    ObjectType GetType() const override;
};

class Bomb : public FallingObject {
public:
    // Zitronen als negative Objekte
    static sf::Texture* tex;

    Bomb();

    Bomb(const float playerPos);

    ObjectType GetType() const override;
};

struct ObjectContainer {
public:
    std::vector<Coin> coins;
    std::vector<Bomb> bombs;
    int getSize() const { return int(coins.size() + bombs.size()); }
};