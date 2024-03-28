#pragma once
#include <SFML/Graphics.hpp>
#include <map>

#include "GameState/GameState.hpp"
#include "GUI/Gui.hpp"

class GameState_LevelMode : public GameState
{
private:
	sf::View view;
	std::map<std::string>

public:
	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

	GameState_LevelMode(const Game* game);
};