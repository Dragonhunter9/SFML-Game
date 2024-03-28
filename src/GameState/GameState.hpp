#pragma once
#include "Game.hpp"

class GameState
{
public:
	Game* game;

	virtual void draw(const float deltaTime) = 0;
	virtual void update(const float deltaTime) = 0;
	virtual void handleInput() = 0;
};