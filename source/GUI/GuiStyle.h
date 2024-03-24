#pragma once
#include <vector>
#include <utility>
#include <string>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"

class GuiStyle
{
public:
	sf::Color bodyCol;
	sf::Color bodyHighlightCol;
	sf::Color borderCol;
	sf::Color borderHighlightCol;
	sf::Color textCol;
	sf::Color textHighlightCol;
	sf::Font* font;

	float borderSize;

	GuiStyle();
	GuiStyle(sf::Font* font, float borderSize, sf::Color bodyCol, sf::Color borderCol, sf::Color textCol, sf::Color, sf::Color bodyHighlightCol, sf::Color borderHighlíghtCol, sf::Color textHighlightCol);
};