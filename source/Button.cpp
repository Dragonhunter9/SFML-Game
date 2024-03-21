#include "Button.h"

Button::Button(const float x, const float y, const float width, const float height, const std::string& buttonText, const sf::Font& font)
    : shape(sf::Vector2f(width, height)), text(buttonText, font, 24) {

    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(70, 130, 180)); // Steel Blue
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.0f);

    text.setPosition(x + (width - text.getGlobalBounds().width) / 2, y + (height - text.getGlobalBounds().height) / 2 - 10);
    text.setFillColor(sf::Color::White);
}

void Button::Draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(text);
}

bool Button::IsMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return shape.getGlobalBounds().contains(mousePosition);
}