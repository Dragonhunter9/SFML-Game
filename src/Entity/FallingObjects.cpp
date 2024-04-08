#include "FallingObjects.hpp"
#include "Utility/Math.hpp"

void FallingObject::Move(const float deltaTime) {
    if (drawObject) {
        object.move(0.0f, velocity * deltaTime);
    }
}

void FallingObject::Draw(sf::RenderWindow& window) const {
    if (drawObject) {
        window.draw(object);
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

FallingObject::FallingObject() : radius(15), object((float)radius), drawObject(true) {
    object.setOrigin(object.getRadius(), object.getRadius());
}

void FallingObject::DrawAllObjects(sf::RenderWindow& window) {
    for (auto& coin : objectsContainer.coins) {
        coin.Draw(window);
    }

    for (auto& bomb : objectsContainer.bombs) {
        bomb.Draw(window);
    }

    //for (int i = 0; i < objectsContainer.getSize(); i++) {
    //    if (i > (int)objectsContainer.coins.size() - 1) {
    //        objectsContainer.bombs[i - objectsContainer.coins.size()].Draw(window);
    //        continue;
    //    }
    //    objectsContainer.coins[i].Draw(window);
    //}

    //for (const std::unique_ptr<FallingObject>& loopObject : objects) {
    //    if (loopObject->drawObject) {
    //        window.draw(loopObject->object);
    //    }
    //}
}

void FallingObject::MoveAllObjects(const float deltaTime) {
    for (auto& coin : objectsContainer.coins) {
        coin.Move(deltaTime);
    }

    for (auto& bomb : objectsContainer.bombs) {
        bomb.Move(deltaTime);
    }
}

void FallingObject::AddPoints(const sf::RenderWindow& window, unsigned int points) {
    for (int i = 0; i < objectsContainer.bombs.size(); i++) {
        if (objectsContainer.bombs[i].TestIfDraw(window)) {
            if (objectsContainer.bombs[i].GetType() == FallingObject::ObjectType::Bomb)
                points++;
            objectsContainer.bombs.erase(objectsContainer.bombs.begin() + i);
        }
    }

    //for (std::unique_ptr<FallingObject>& loopObject : objects) {
    //    if (loopObject->TestIfDraw(window) && loopObject->GetType() == FallingObject::ObjectType::Bomb) {
    //        points++;
    //    }
    //}
}

sf::FloatRect FallingObject::GetGlobalBounds() const {
    return object.getGlobalBounds();
}

// static variables
sf::Clock FallingObject::timer;
std::vector<std::unique_ptr<FallingObject>> FallingObject::objects;
ObjectContainer FallingObject::objectsContainer;
float FallingObject::pauseTime;
float FallingObject::velocity = 100.0f;

sf::Texture* Coin::tex;
sf::Texture* Bomb::tex;

Coin::Coin() {
    object.setFillColor(sf::Color::Yellow);
    object.setPosition((float)Math::RandomNumber((int)object.getRadius(), 800 - (int)object.getRadius()), -20.f);
    object.setTexture(tex);
}

FallingObject::ObjectType Coin::GetType() const { return ObjectType::Coin; }

Bomb::Bomb() {
    object.setFillColor(sf::Color(128, 128, 128));
    object.setPosition((float)Math::RandomNumber(radius, 800 - radius), -10.f);
}

Bomb::Bomb(const float playerPos) {
    //object.setFillColor(sf::Color(128, 128, 128));
    object.setPosition(playerPos, -10.f);
    object.setTexture(tex);
}

FallingObject::ObjectType Bomb::GetType() const { return ObjectType::Bomb; }