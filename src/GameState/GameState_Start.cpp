#include "GameState_Start.hpp"
#include "GameState_LevelMode.hpp"

void GameState_Start::draw(const float deltaTime)
{
	game->window.draw(gui);
}

void GameState_Start::update(const float deltaTime) {
	gui.highlight(gui.getEntry((sf::Vector2f)sf::Mouse::getPosition(game->window)));
}

void GameState_Start::handleInput()
{
	sf::Event event;
	while (game->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			game->window.close();
		if (event.mouseButton.button == sf::Mouse::Left) {
			const std::string message = gui.activate((sf::Vector2f)sf::Mouse::getPosition(game->window));
			if (message == "levelmode")
				game->pushState(new GameState_LevelMode(game));
			else if (message == "exit")
				game->window.close();
		}
	}
}

GameState_Start::GameState_Start(Game* game) : gui({400, 50}, 10, false, game->guiStylesheets.at("standard"), {std::make_pair("Level-Mode", "levelmode"), std::make_pair("Exit", "exit")})
{
	this->game = game;
	gui.setPosition((float)game->windowWidth / 2, (float)game->windowHeight / 2);
	gui.show();
}