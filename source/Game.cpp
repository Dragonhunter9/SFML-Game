#include "Game.hpp"

void Game::createLevels() {
    levels.reserve(5);
    levels.emplace_back(1, 1, 100.0f, sf::Vector2i(1, 5), 4);
    levels.emplace_back(2, 10, 120.0f, sf::Vector2i(1, 4), 4);
    levels.emplace_back(3, 10, 160.0f, sf::Vector2i(1, 3), 3);
    levels.emplace_back(4, 10, 180.0f, sf::Vector2i(0, 3), 3);
    levels.emplace_back(5, 10, 200.0f, sf::Vector2i(0, 2), 2);
    currentLevel = 0;
}

void Game::updateLevel() {
    if (player.score >= levels[currentLevel].GetRequiredScore()) {
        gameStatus = Won;
        FallingObject::objects.clear();
        currentLevel++;
        player.score = 0;
        player.lives = 3;
        FallingObject::velocity = levels[currentLevel].GetFallingSpeed();
    }
}

void Game::nextLevel() {
    gameStatus = Running;
    player.ResetPosition(window);
    deltaTimeClock.restart();
    FallingObject::timer.restart();
}

void Game::resetLevel() {
    FallingObject::objects.clear();
    player.score = 0;
    player.lives = 3;
    player.ResetPosition(window);
    deltaTimeClock.restart();
    FallingObject::timer.restart();

    gameStatus = Running;
}

void Game::loadGuiConfigs() {
    guiSystem.emplace("menu", owngui::Gui(sf::Vector2f(192, 32), 4, false, guiStyle, { std::make_pair("Pause", "pause") }));
}

void Game::displayPauseScreen() {
    std::vector<std::pair<std::string, std::string>> vec = {

    { "Entry 1", "First entry" },

    { "Entry 2", "Second entry" }

    };

    owngui::GuiStyle style(&font, 1,

        sf::Color(0xc6, 0xc6, 0xc6), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00),

        sf::Color(0x61, 0x61, 0x61), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00)

    );

    owngui::Gui gui(sf::Vector2f(192, 32), 4, false, style, vec);

    //gui.setPosition(200,200);
    //gui.setOrigin(96, 16);
    //gui.show();

    guiSystem.at("menu").setPosition(200, 200);
    guiSystem.at("menu").setOrigin(96, 16);
    guiSystem.at("menu").show();

    for (auto& gui : this->guiSystem) window.draw(gui.second);

    /*tgui::Gui pauseGUI(window);

    auto button = tgui::Button::create("Pause");
    button->setSize(tgui::Layout2d("50%", "12.5%"));
    button->setPosition(tgui::Layout2d("25%", "43.75%"));
    button->setTextSize(24);

    pauseGUI.add(button);
    pauseGUI.draw();*/
}

void Game::displayTGUIWonScreen() {
    if (levels.size() > currentLevel) {
        //tgui::Gui wonGUI(window);

        //auto panel = tgui::Panel::create();
        //panel->setPosition(tgui::Layout2d("25%", "25%"));
        //panel->setSize(tgui::Layout2d("50%", "50%"));
        //wonGUI.add(panel);
        //
        //auto label = tgui::Label::create("Congratulations!\nLevel " + std::to_string(currentLevel) + " completed\n\nPress ENTER to continue");
        //label->setPosition(tgui::Layout2d("25%", "35%"));
        //label->setSize(tgui::Layout2d("50%", "50%"));
        //label->setTextSize(24);
        //label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
        //wonGUI.add(label);

        /*auto button = tgui::Button::create("Continue");
        button->setPosition(tgui::Layout2d("50%", "40%"));
        button->setSize(tgui::Layout2d("40%", "10%"));
        button->onPress(NextLevel);
        wonGUI.add(button);*/

        //wonGUI.draw();
    }
}

void Game::displayWonScreen() {
    if (levels.size() > currentLevel) {
        sf::RectangleShape backGround(sf::Vector2f(400, 200));
        backGround.setPosition(window.getSize().x / 2.0f - 200, window.getSize().y / 2.0f - 100);
        backGround.setFillColor(sf::Color(100, 149, 237)); // Dodger Blue

        sf::Text wonText("Congratulations!", font, 40);
        wonText.setPosition(window.getSize().x / 2.0f - wonText.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - 70);
        wonText.setFillColor(sf::Color::White);

        sf::Text levelText("Level " + std::to_string(currentLevel) + " completed", font, 30);
        levelText.setPosition(window.getSize().x / 2.0f - levelText.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - 20);
        levelText.setFillColor(sf::Color::White);

        //Button continueButton(window.getSize().x / 2.0f - 50, window.getSize().y / 2.0f + 30, 105, 45, "Continue", font);
        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButton.IsMouseOver(window))
        //    NextLevel();

        window.draw(backGround);
        window.draw(wonText);
        window.draw(levelText);
        //continueButton.Draw(window);
        return;
    }

    sf::RectangleShape backGround(sf::Vector2f(400, 200));
    backGround.setPosition(window.getSize().x / 2.0f - 200, window.getSize().y / 2.0f - 100);
    backGround.setFillColor(sf::Color(100, 149, 237)); // Dodger Blue

    sf::Text wonText("Congratulations!", font, 40);
    wonText.setPosition(window.getSize().x / 2.0f - wonText.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - 70);
    wonText.setFillColor(sf::Color::White);

    sf::Text levelText("Game completed", font, 30);
    levelText.setPosition(window.getSize().x / 2.0f - levelText.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - 20);
    levelText.setFillColor(sf::Color::White);

    //Button continueButton(window.getSize().x / 2.0f - 50, window.getSize().y / 2.0f + 30, 125, 45, "End Game", font);
    //if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButton.IsMouseOver(window)) {
    //    window.close();
    //}

    window.draw(backGround);
    window.draw(wonText);
    window.draw(levelText);
    //continueButton.Draw(window);
}

void Game::displayGameOverScreen() {
    sf::RectangleShape backGround(sf::Vector2f(400, 200));
    backGround.setPosition(window.getSize().x / 2.0f - 200, window.getSize().y / 2.0f - 100);
    backGround.setFillColor(sf::Color(100, 149, 237)); // Dodger Blue

    sf::Text wonText("Game over!", font, 40);
    wonText.setPosition(window.getSize().x / 2.0f - wonText.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - 70);
    wonText.setFillColor(sf::Color::White);

    //Button continueButton(window.getSize().x / 2.0f - 50, window.getSize().y / 2.0f + 30, 125, 45, "Try again", font);
    //if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButton.IsMouseOver(window)) {
    //    ResetLevel();
    //}

    window.draw(backGround);
    window.draw(wonText);
    //continueButton.Draw(window);
}

void Game::DrawGame() {
    window.clear();
    FallingObject::DrawAllObjects(window);
    player.Draw(window);

    window.draw(scoreDisplay);
    window.draw(levelDisplay);
    player.DrawLives(window);

    if (gameStatus == Paused)
        displayPauseScreen();
    if (gameStatus == Won)
        displayTGUIWonScreen();
    if (gameStatus == GameOver)
        displayGameOverScreen();

    //gameGUI.draw();

    window.display();
}

void Game::UpdateGame() {
    // FallingObject::AddPoints(window, player.score);

    scoreDisplay.setString(std::to_string(player.score));
    levelDisplay.setString("Level " + std::to_string(currentLevel + 1));
    updateLevel();

    if (FallingObject::timer.getElapsedTime().asSeconds() + FallingObject::pauseTime > objectSpawnTime) {
        objectSpawnTime = RandomNumber(levels[currentLevel].GetSpawnSpeed().x, levels[currentLevel].GetSpawnSpeed().y);
        FallingObject::pauseTime = 0;
        if (RandomNumber(1, levels[currentLevel].GetBombPossiblity()) != levels[currentLevel].GetBombPossiblity()) {
            Coin coin;
            //FallingObject::objects.emplace_back(std::make_unique<Coin>());
            FallingObject::objects.emplace_back(new Coin);
        }
        else {
            Bomb bomb(player.GetPosition().x);
            FallingObject::objects.emplace_back(new Bomb);
        }

        FallingObject::timer.restart();
    }

    sf::Time deltaTime = deltaTimeClock.restart();
    float deltaTimeSeconds = deltaTime.asSeconds();

    player.Move(window, deltaTimeSeconds);
    FallingObject::MoveAllObjects(deltaTimeSeconds);

    if (player.lives < 1) {
        gameStatus = GameOver;
    }

    player.Collided();
}

void Game::ProcessEventsAndInputs() {
    sf::Event event;
    while (window.pollEvent(event)) {
        //gameGUI.handleEvent(event);

        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::P:
                switch (gameStatus) {
                case Running:
                    gameStatus = Paused;
                    FallingObject::pauseTime = FallingObject::timer.getElapsedTime().asSeconds();
                    break;
                case Paused:
                    gameStatus = Running;
                    deltaTimeClock.restart();
                    FallingObject::timer.restart();
                    break;
                }
                break;
            case sf::Keyboard::Enter:
                switch (gameStatus) {
                case GameOver:
                    resetLevel();
                    break;
                case Won:
                    if (levels.size() > currentLevel)
                        nextLevel();
                    break;
                }
                break;
            }
            break;

        case sf::Event::MouseButtonPressed:
            switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                if (guiSystem.at("menu").visible) {
                    std::string msg = guiSystem.at("menu").activate((sf::Vector2f)sf::Mouse::getPosition(window));
                    if (msg == "pause")
                    {
                        gameStatus = Running;
                        deltaTimeClock.restart();
                        FallingObject::timer.restart();
                    }
                }
            }
            break;
        }



        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                //std::string msg = this->guiSystem.at("menu").activate(mousePos);
                //
                //if (msg == "load_game")
                //{
                //    this->loadgame();
                //}
            }
            break;
        }
    }
}

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "Bounce Ball"),
               player(window),
               scoreDisplay(std::to_string(player.score), font, 24),
               deltaTimeClock(),
               gameStatus(Running),
               levelDisplay("Level: " + std::to_string(currentLevel + 1), font, 24),
               //gameGUI(window),
               guiStyle(&font, 1, sf::Color(0xc6, 0xc6, 0xc6), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00), sf::Color(0x61, 0x61, 0x61), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00))
{
    font.loadFromFile("arial.ttf");
    createLevels();
    objectSpawnTime = RandomNumber(levels[currentLevel].GetSpawnSpeed().x, levels[currentLevel].GetSpawnSpeed().y);
    //tgui::Theme::setDefault("vendor/TGUI/themes/Black.txt");
    loadGuiConfigs();
}

void Game::RunGame() {
    scoreDisplay.setPosition(window.getSize().x / 2.0f, 10);
    levelDisplay.setPosition(10, 10);
    FallingObject::objects.reserve(20);

    FallingObject::timer.restart();

    while (window.isOpen()) {
        ProcessEventsAndInputs();

        if (gameStatus == Running)
            UpdateGame();

        DrawGame();
    }
}