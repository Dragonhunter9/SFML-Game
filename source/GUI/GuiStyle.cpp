#include "GuiStyle.h"

GuiStyle::GuiStyle() : borderSize(0.0f), font(nullptr) {}

GuiStyle::GuiStyle(sf::Font* font, float borderSize, sf::Color bodyCol, sf::Color borderCol, sf::Color textCol, sf::Color, sf::Color bodyHighlightCol, sf::Color borderHighl�ghtCol, sf::Color textHighlightCol)
	: bodyCol(bodyCol), bodyHighlightCol(bodyHighlightCol), borderCol(borderCol), borderHighlightCol(borderHighlightCol), textCol(textCol), textHighlightCol(textHighlightCol), font(font), borderSize(borderSize)
{}