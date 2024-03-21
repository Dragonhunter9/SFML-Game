#include "FallingObject.h"

void FallingObject::Move(const float& deltaTime) {
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

FallingObject::FallingObject() : object(8.0f), drawObject(true) {}

void FallingObject::DrawAllObjects(sf::RenderWindow& window) {
    for (const std::unique_ptr<FallingObject>& loopObject : objects) {
        if (loopObject->drawObject) {
            window.draw(loopObject->object);
        }
    }
}

void FallingObject::MoveAllObjects(const float& deltaTime) {
    for (std::unique_ptr<FallingObject>& loopObject : objects) {
        loopObject->Move(deltaTime);
    }
}

void FallingObject::AddPoints(const sf::RenderWindow& window, unsigned int& points) {
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