#include "Coin.h"

#include "CustomFunctions.h"

Coin::Coin() {
    object.setFillColor(sf::Color::Yellow);
    object.setPosition((float)RandomNumber((int)object.getRadius(), 800 - (int)object.getRadius()), -20.f);
}