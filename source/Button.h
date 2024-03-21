#pragma once
#include "SFML/Graphics.hpp"

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;

public:
    Button(const float x, const float y, const float width, const float height, const std::string& buttonText, const sf::Font& font);

    void Draw(sf::RenderWindow& window) const;

    bool IsMouseOver(const sf::RenderWindow& window) const;
};