#include "FallingObjects.hpp"

int RandomNumber(const int min, const int max);

void FallingObject::Move(const float deltaTime) {
    if (drawObject) {
        object.move(0.0f, velocity * deltaTime);
    }
}

bool FallingObject::TestIfDraw(const sf::RenderWindow& window) {
    if (object.getPosition().y > window.getSize().y - 15 && drawObject == true) {
        drawObject = false;
        return true;
    }
    return false;
}

FallingObject::ObjectType FallingObject::GetType() const { return ObjectType::FallingObj; }

FallingObject::FallingObject() : object(10.0f), drawObject(true) {}

void FallingObject::DrawAllObjects(sf::RenderWindow& window) {
    for (const std::unique_ptr<FallingObject>& loopObject : objects) {
        if (loopObject->drawObject) {
            window.draw(loopObject->object);
        }
    }
}

void FallingObject::MoveAllObjects(const float deltaTime) {
    for (std::unique_ptr<FallingObject>& loopObject : objects) {
        loopObject->Move(deltaTime);
    }
}

void FallingObject::AddPoints(const sf::RenderWindow& window, unsigned int points) {
    for (const std::unique_ptr<FallingObject>& loopObject : objects) {
        if (loopObject->TestIfDraw(window) && loopObject->GetType() == FallingObject::ObjectType::Bomb) {
            points++;
        }
    }
}

sf::FloatRect FallingObject::GetGlobalBounds() const {
    return object.getGlobalBounds();
}

sf::Clock FallingObject::timer;
std::vector<std::unique_ptr<FallingObject>> FallingObject::objects;
float FallingObject::pauseTime;
float FallingObject::velocity = 100.0f;

Coin::Coin() {
    object.setFillColor(sf::Color::Yellow);
    object.setPosition((float)RandomNumber((int)object.getRadius(), 800 - (int)object.getRadius()), -20.f);
}

FallingObject::ObjectType Coin::GetType() const { return ObjectType::Coin; }

Bomb::Bomb() {
    object.setFillColor(sf::Color(128, 128, 128));
    object.setPosition((float)RandomNumber((int)object.getRadius(), 800 - (int)object.getRadius()), -20.f);
}

Bomb::Bomb(const float playerPos) {
    object.setFillColor(sf::Color(128, 128, 128));
    object.setPosition(playerPos, -20.f);
}

FallingObject::ObjectType Bomb::GetType() const { return ObjectType::Bomb; }