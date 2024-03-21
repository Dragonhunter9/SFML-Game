#include "Bomb.h"

#include "CustomFunctions.h"

Bomb::Bomb() {
    object.setFillColor(sf::Color(128, 128, 128));
    object.setPosition((float)RandomNumber((int)object.getRadius(), 800 - (int)object.getRadius()), -20.f);
}

Bomb::Bomb(const float& playerPos) {
    object.setFillColor(sf::Color(128, 128, 128));
    object.setPosition(playerPos, -20.f);
}