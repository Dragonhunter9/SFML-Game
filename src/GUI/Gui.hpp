#pragma once
#include <vector>
#include <utility>
#include <string>

#include "SFML/Graphics.hpp"

class GuiStyle {
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
	GuiStyle(sf::Font* font, float borderSize, sf::Color bodyCol, sf::Color borderCol, sf::Color textCol, sf::Color bodyHighlightCol, sf::Color borderHighlíghtCol, sf::Color textHighlightCol);
};

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

class Gui : public sf::Transformable, public sf::Drawable
{
private:
	// If true the menu entries will be horizontally, not vertically, adjacent
	bool horizontal;
	GuiStyle style;
	sf::Vector2f dimensions;
	int padding;

public:
	std::vector<GuiEntry> entries;
	bool visible;

	Gui(sf::Vector2f dimensions, int padding, bool horizontal, GuiStyle& style, std::vector<std::pair<std::string, std::string>> entries);

	sf::Vector2f getSize();
	
	// Return the entry the mouse is hovering over. Return -1 if the mouse is outside of the gui
	int getEntry(const sf::Vector2f mousePos);

	// Change text of an entry
	void setEntryText(int entry, const std::string& text);

	// Change entry dimensions
	void setDimensions(sf::Vector2f dimensions);

	// Draw menu
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void show();

	void hide();

	// Highlights an entry of the menu
	void highlight(const int entry);

	// Return message bound to the entry
	std::string activate(const int entry);
	std::string activate(const sf::Vector2f mousePos);
};