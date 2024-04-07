#include "Game.hpp"
#include "GameState/GameState.hpp"
#include "Utility/Math.hpp"

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "Bounce Ball", sf::Style::Titlebar | sf::Style::Close)
{
    font.loadFromFile("assets/fonts/arial.ttf");
    loadStylesheets();
    loadTextures();
    //window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);
}

Game::~Game()
{
    while (!states.empty())
        popState();
}

void Game::loadTextures()
{
    texmgr.loadTexture("player", "assets/textures/playerTexture.png");
}

void Game::loadStylesheets()
{
    guiStylesheets.emplace("standard", GuiStyle(&font, 2,
        sf::Color(20, 20, 20),           // bodyCol: Dunkelgrau
        sf::Color(50, 50, 50),           // borderCol: Dunkelgrau
        sf::Color::White,                // textCol: Weiß
        sf::Color(100, 100, 255),        // bodyHighlightCol: Hellblau
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
        window.clear();
        peekState()->draw(deltaTime);
        window.display();
    }
}