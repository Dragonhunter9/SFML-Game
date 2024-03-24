#include "GuiEntry.h"

GuiEntry::GuiEntry() {}

GuiEntry::GuiEntry(const std::string& message, sf::RectangleShape shape, sf::Text text)
	: message(message), shape(shape), text(text)
{}