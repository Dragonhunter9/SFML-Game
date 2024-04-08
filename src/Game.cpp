#include "Game.hpp"
#include "GameState/GameState.hpp"
#include "Utility/Math.hpp"

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "Cat Catcher", sf::Style::Titlebar | sf::Style::Close)
{
    font.loadFromFile("assets/fonts/arial.ttf");
    loadStylesheets();
    loadTextures();
}

Game::~Game()
{
    while (!states.empty())
        popState();
}

void Game::loadTextures()
{
    texmgr.loadTexture("player", "assets/textures/playerTexture.png");
    texmgr.loadTexture("coin", "assets/textures/coinTexture.png");
    texmgr.loadTexture("bomb", "assets/textures/bombTexture.png");
}

void Game::loadStylesheets()
{
    guiStylesheets.emplace("standard", GuiStyle(&font, 2,
        sf::Color(120, 120, 140),        // bodyCol: Dunkles Blaugrau
        sf::Color(50, 50, 50),           // borderCol: Dunkelgrau
        sf::Color::White,                // textCol: Weiß
        sf::Color(150, 150, 255),        // bodyHighlightCol: Hellblau
        sf::Color(70, 70, 150),          // borderHighlightCol: Helleres Blau
        sf::Color::Black));              // textHighlightCol: Schwarz
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
        window.clear(sf::Color(100, 120, 140));
        peekState()->draw(deltaTime);
        window.display();
    }
}