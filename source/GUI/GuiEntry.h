#pragma once
#include "SFML/Graphics.hpp"

class GuiEntry
{
public:
	// Handles apperence of the entry
	sf::RectangleShape shape;
	// String return when the entry is activated
	std::string message;
	// Text displayed on the entry
	sf::Text text;

	GuiEntry();
	GuiEntry(const std::string& message, sf::RectangleShape shape, sf::Text text);
};