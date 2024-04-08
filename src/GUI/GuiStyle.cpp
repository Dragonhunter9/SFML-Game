#include "GuiStyle.hpp"

GuiStyleT::GuiStyleT() : borderSize(0.0f), font(nullptr) {}

GuiStyleT::GuiStyleT(sf::Font* font, float borderSize, sf::Color bodyCol, sf::Color borderCol, sf::Color textCol, sf::Color bodyHighlightCol, sf::Color borderHighlíghtCol, sf::Color textHighlightCol)
	: bodyCol(bodyCol), bodyHighlightCol(bodyHighlightCol), borderCol(borderCol), borderHighlightCol(borderHighlíghtCol), textCol(textCol), textHighlightCol(textHighlightCol), font(font), borderSize(borderSize)
{}