#pragma once
#include <stack>
#include "SFML/Graphics.hpp"
#include "Entity/Player.hpp"
#include "GUI/Gui.hpp"
#include "Utility/Math.hpp"

class GameState;

class Game {
private:
    //void loadTextures();
    void loadStylesheets();
    //void loadFonts();

public:
    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window;
    sf::Font font;
    std::stack<GameState*> states;

    //tgui::Gui gameGUI;
    std::map<std::string, GuiStyle> guiStylesheets;
    std::map<std::string, Gui> guiSystem;

    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* peekState();

    void gameloop();

    Game();
    ~Game();
};