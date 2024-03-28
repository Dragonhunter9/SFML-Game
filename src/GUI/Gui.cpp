#include "Gui.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace owngui {
	GuiStyle::GuiStyle() : borderSize(0.0f), font(nullptr) {}

	GuiStyle::GuiStyle(sf::Font* font, float borderSize, sf::Color bodyCol, sf::Color borderCol, sf::Color textCol, sf::Color bodyHighlightCol, sf::Color borderHighlíghtCol, sf::Color textHighlightCol)
		: bodyCol(bodyCol), bodyHighlightCol(bodyHighlightCol), borderCol(borderCol), borderHighlightCol(borderHighlíghtCol), textCol(textCol), textHighlightCol(textHighlightCol), font(font), borderSize(borderSize)
	{}

	GuiEntry::GuiEntry() {}

	GuiEntry::GuiEntry(const std::string& message, sf::RectangleShape shape, sf::Text text)
		: message(message), shape(shape), text(text)
	{}

	Gui::Gui(sf::Vector2f dimensions, int padding, bool horizontal, GuiStyle& style, std::vector<std::pair<std::string, std::string>> entries)
		: visible(false), horizontal(horizontal), style(style), dimensions(dimensions), padding(padding)
	{
		sf::RectangleShape shape;
		shape.setSize(dimensions);
		shape.setFillColor(style.bodyCol);
		shape.setOutlineThickness(-style.borderSize);
		shape.setOutlineColor(style.borderCol);

		for (auto& entry : entries) {
			sf::Text text;
			text.setString(entry.first);
			text.setFont(*style.font);
			text.setFillColor(style.textCol);
			text.setCharacterSize((int)(dimensions.y - style.borderSize - padding));

			this->entries.emplace_back(entry.second, shape, text);
		}
	}

	sf::Vector2f Gui::getSize()
	{
		return sf::Vector2f(dimensions.x, dimensions.y * entries.size());
	}

	int Gui::getEntry(const sf::Vector2f mousePos)
	{
		if (entries.size() == 0)
			return -1;
		if (this->visible == false)
			return -1;

		for (int i = 0; i < entries.size(); i++) {
			sf::Vector2f point = mousePos;
			point += this->entries[i].shape.getOrigin();
			point -= this->entries[i].shape.getPosition();

			if (point.x < 0 || point.x > this->entries[i].shape.getScale().x * dimensions.x)
				continue;
			if (point.y < 0 || point.y > this->entries[i].shape.getScale().y * dimensions.y)
				continue;
			return i;
		}
		return -1;
	}

	void Gui::setEntryText(int entry, const std::string& text)
	{
		if (entry >= entries.size() || entry < 0)
			return;

		entries[entry].text.setString(text);
	}

	void Gui::setDimensions(sf::Vector2f dimensions)
	{
		this->dimensions = dimensions;

		for (auto& entry : this->entries) {
			entry.shape.setSize(dimensions);
			entry.text.setCharacterSize((int)(dimensions.y - style.borderSize - padding));
		}
	}

	void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (!this->visible) return;

		/* Draw each entry of the menu. */
		for (auto& entry : this->entries)
		{
			/* Draw the entry. */
			target.draw(entry.shape);
			target.draw(entry.text);
		}

		return;
	}

	void Gui::show() {
		sf::Vector2f offset(0.0f, 0.0f);
		visible = true;

		for (auto& entry : entries) {
			sf::Vector2f origin = getOrigin();
			origin -= offset;
			entry.shape.setOrigin(origin);
			entry.text.setOrigin(origin);

			entry.shape.setPosition(getPosition());
			entry.text.setPosition(getPosition());

			if (horizontal)
				offset.x += dimensions.x;
			else
				offset.y += dimensions.y;
		}
	}

	void Gui::hide() {
		visible = false;
	}

	void Gui::highlight(const int entry) {
		for (int i = 0; i < entries.size(); i++) {
			if (i == entry) {
				entries[i].shape.setFillColor(style.bodyHighlightCol);
				entries[i].shape.setOutlineColor(style.borderHighlightCol);
				entries[i].text.setFillColor(style.textHighlightCol);
			}

			else {
				entries[i].shape.setFillColor(style.bodyCol);
				entries[i].shape.setOutlineColor(style.borderCol);
				entries[i].text.setFillColor(style.textCol);
			}
		}
	}

	std::string Gui::activate(const int entry) {
		if (entry == -1)
			return "";

		return entries[entry].message;
	}

	std::string Gui::activate(sf::Vector2f mousePos) {
		int entry = getEntry(mousePos);
		return activate(entry);
	}
}