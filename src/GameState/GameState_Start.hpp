#pragma once
#include "GameState.hpp"
#include "GUI/Gui.hpp"

class GameState_Start :
    public GameState
{
private:
	Gui gui;

public:
	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

	GameState_Start(Game* game);
};