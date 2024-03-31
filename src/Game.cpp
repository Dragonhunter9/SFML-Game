#include "Game.hpp"
#include "GameState/GameState.hpp"
#include "Utility/Math.hpp"

//void Game::loadGuiConfigs() {
//    guiSystem.emplace("menu", Gui(sf::Vector2f(192, 32), 4, false, guiStyle, { std::make_pair("Pause", "pause") }));
//}
//

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "Bounce Ball", 7U)
               //guiStyle(&font, 1, sf::Color(0xc6, 0xc6, 0xc6), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00), sf::Color(0x61, 0x61, 0x61), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00))
{
    font.loadFromFile("assets/fonts/arial.ttf");
    window.setFramerateLimit(60);
    //loadGuiConfigs();
}

Game::~Game()
{
    while (!states.empty())
        popState();
}

void Game::loadStylesheets()
{
}

void Game::pushState(GameState* state)
{
    states.push(state);
}

void Game::popState()
{
    delete states.top();
    states.pop();
}

void Game::changeState(GameState* state)
{
    if (!states.empty())
        popState();
    pushState(state);
}

GameState* Game::peekState()
{
    if (states.empty())
        return nullptr;
    return states.top();
}

void Game::gameloop()
{
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        const float deltaTime = elapsed.asSeconds();

        if (peekState() == nullptr)
            continue;
        peekState()->handleInput();
        peekState()->update(deltaTime);
        window.clear();
        peekState()->draw(deltaTime);
        window.display();
    }
}