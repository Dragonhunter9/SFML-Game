#include "GameState_LevelMode.hpp"

Level::Level() : levelNumber(0), requiredScore(1), fallingSpeed(100.0f), spawnSpeed(sf::Vector2i(1, 4)), bombPossibility(4) {}

Level::Level(const int number, const int score, const float speed, const sf::Vector2i spawningSpeed, const int bombSpawnPossibility)
    : levelNumber(number), requiredScore(score), fallingSpeed(speed), spawnSpeed(spawningSpeed), bombPossibility(bombSpawnPossibility) {}

int Level::GetLevelNumber() const { return levelNumber; };

int Level::GetRequiredScore() const { return requiredScore; }

float Level::GetFallingSpeed() const { return fallingSpeed; }

sf::Vector2i Level::GetSpawnSpeed() const { return spawnSpeed; }

int Level::GetBombPossiblity() const { return bombPossibility; }

void GameState_LevelMode::draw(const float deltaTime)
{
    game->window.draw(scoreDisplay);
    game->window.draw(levelDisplay);
    player.DrawLives(game->window);

    FallingObject::DrawAllObjects(game->window);
    game->window.draw(player);

    if (gameStatus == Paused)
        displayPauseScreen();
    if (gameStatus == Won)
        displayWonScreen();
    if (gameStatus == GameOver)
        displayGameOverScreen();
}

void GameState_LevelMode::update(const float deltaTime)
{
    if (gameStatus == Running) {
        if (FallingObject::timer.getElapsedTime().asSeconds() + FallingObject::pauseTime > objectSpawnTime) {
            objectSpawnTime = Math::RandomNumber(levels[currentLevel].GetSpawnSpeed().x, levels[currentLevel].GetSpawnSpeed().y);
            FallingObject::pauseTime = 0;
            if (Math::RandomNumber(1, levels[currentLevel].GetBombPossiblity()) != levels[currentLevel].GetBombPossiblity()) {
                FallingObject::objectsContainer.coins.emplace_back();
                //FallingObject::objects.emplace_back(new Coin);
            }
            else {
                FallingObject::objectsContainer.bombs.emplace_back(player.GetPosition().x);
                //FallingObject::objects.emplace_back(new Bomb(player.GetPosition().x));
            }
            FallingObject::timer.restart();
        }
        player.Move(game->window, deltaTime);
        FallingObject::MoveAllObjects(deltaTime);

        if (true) {//player.Collided()) {
            scoreDisplay.setString(std::to_string(player.score));
            levelDisplay.setString("Level " + std::to_string(currentLevel + 1));
            updateLevel();
            if (player.lives < 1) {
                gameStatus = GameOver;
            }
        }
    }
}

void GameState_LevelMode::handleInput()
{
    sf::Event event;
    while (game->window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            game->window.close();
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::P:
                switch(gameStatus) {
                case Running:
                    gameStatus = Paused;
                    FallingObject::pauseTime = FallingObject::timer.getElapsedTime().asSeconds();
                    break;
                case Paused:
                    gameStatus = Running;
                    FallingObject::timer.restart();
                    break;
                }
                break;
            case sf::Keyboard::Enter:
                if (gameStatus == GameOver)
                    resetLevel();
                else if (gameStatus == Won && levels.size() > currentLevel)
                    nextLevel();
                break;
        }
        break;
        case sf::Event::MouseButtonPressed:
            switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                if (guiSystem.at("pauseMenu").visible) {
                    const std::string msg = guiSystem.at("pauseMenu").activate((sf::Vector2f)sf::Mouse::getPosition(game->window));
                    if (msg == "continue") {
                        gameStatus = Running;
                        FallingObject::timer.restart();
                    }
                    if (msg == "exit") {
                        game->window.close();
                    }
                }
                break;
            }
            break;
        }
    }
}

constexpr void GameState_LevelMode::createLevels() {
    levels.reserve(5);
    levels.emplace_back(1, 10, 100.0f, sf::Vector2i(1, 5), 4);
    levels.emplace_back(2, 10, 120.0f, sf::Vector2i(1, 4), 4);
    levels.emplace_back(3, 10, 160.0f, sf::Vector2i(1, 3), 3);
    levels.emplace_back(4, 10, 180.0f, sf::Vector2i(0, 3), 3);
    levels.emplace_back(5, 10, 200.0f, sf::Vector2i(0, 2), 2);
    currentLevel = 0;
}

void GameState_LevelMode::updateLevel() {
    if (player.score + 1 > levels[currentLevel].GetRequiredScore()) {
        gameStatus = Won;
        FallingObject::objectsContainer.coins.clear();
        FallingObject::objectsContainer.bombs.clear();
        currentLevel++;
        player.score = 0;
        player.lives = 3;
        FallingObject::velocity = levels[currentLevel].GetFallingSpeed();
    }
}

void GameState_LevelMode::nextLevel() {
    player.ResetPosition(game->window);
    scoreDisplay.setString(std::to_string(player.score));
    levelDisplay.setString("Level " + std::to_string(currentLevel + 1));
    FallingObject::timer.restart();

    gameStatus = Running;
}

void GameState_LevelMode::resetLevel() {
    FallingObject::objectsContainer.coins.clear();
    FallingObject::objectsContainer.bombs.clear();
    player.score = 0;
    player.lives = 3;
    player.ResetPosition(game->window);
    scoreDisplay.setString(std::to_string(player.score));
    levelDisplay.setString("Level " + std::to_string(currentLevel + 1));
    FallingObject::timer.restart();

    gameStatus = Running;
}

void GameState_LevelMode::loadGUI()
{
    guiSystem.emplace("pauseMenu", Gui(sf::Vector2f(192, 32), 4, false, game->guiStylesheets.at("standard"), {std::make_pair("Continue", "continue"), std::make_pair("Exit", "exit")}));
    guiSystem.at("pauseMenu").setPosition((float)game->windowWidth / 2, (float)game->windowHeight / 2);
}

void GameState_LevelMode::displayPauseScreen() {
    guiSystem.at("pauseMenu").show();

    game->window.draw(guiSystem.at("pauseMenu"));

    /*tgui::Gui pauseGUI(window);

    auto button = tgui::Button::create("Pause");
    button->setSize(tgui::Layout2d("50%", "12.5%"));
    button->setPosition(tgui::Layout2d("25%", "43.75%"));
    button->setTextSize(24);

    pauseGUI.add(button);
    pauseGUI.draw();*/
}

void GameState_LevelMode::displayTGUIWonScreen() {
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

void GameState_LevelMode::displayWonScreen() {
    if (levels.size() > currentLevel) {
        sf::RectangleShape backGround(sf::Vector2f(400, 200));
        backGround.setPosition(game->window.getSize().x / 2.0f - 200, game->window.getSize().y / 2.0f - 100);
        backGround.setFillColor(sf::Color(100, 149, 237)); // Dodger Blue

        sf::Text wonText("Congratulations!", game->font, 40);
        wonText.setPosition(game->window.getSize().x / 2.0f - wonText.getGlobalBounds().width / 2.0f, game->window.getSize().y / 2.0f - 70);
        wonText.setFillColor(sf::Color::White);

        sf::Text levelText("Level " + std::to_string(currentLevel) + " completed", game->font, 30);
        levelText.setPosition(game->window.getSize().x / 2.0f - levelText.getGlobalBounds().width / 2.0f, game->window.getSize().y / 2.0f - 20);
        levelText.setFillColor(sf::Color::White);

        //Button continueButton(window.getSize().x / 2.0f - 50, window.getSize().y / 2.0f + 30, 105, 45, "Continue", font);
        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButton.IsMouseOver(window))
        //    NextLevel();

        game->window.draw(backGround);
        game->window.draw(wonText);
        game->window.draw(levelText);
        //continueButton.Draw(window);
        return;
    }

    sf::RectangleShape backGround(sf::Vector2f(400, 200));
    backGround.setPosition(game->window.getSize().x / 2.0f - 200, game->window.getSize().y / 2.0f - 100);
    backGround.setFillColor(sf::Color(100, 149, 237)); // Dodger Blue

    sf::Text wonText("Congratulations!", game->font, 40);
    wonText.setPosition(game->window.getSize().x / 2.0f - wonText.getGlobalBounds().width / 2.0f, game->window.getSize().y / 2.0f - 70);
    wonText.setFillColor(sf::Color::White);

    sf::Text levelText("Game completed", game->font, 30);
    levelText.setPosition(game->window.getSize().x / 2.0f - levelText.getGlobalBounds().width / 2.0f, game->window.getSize().y / 2.0f - 20);
    levelText.setFillColor(sf::Color::White);

    //Button continueButton(window.getSize().x / 2.0f - 50, window.getSize().y / 2.0f + 30, 125, 45, "End Game", font);
    //if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButton.IsMouseOver(window)) {
    //    window.close();
    //}

    game->window.draw(backGround);
    game->window.draw(wonText);
    game->window.draw(levelText);
    //continueButton.Draw(window);
}

void GameState_LevelMode::displayGameOverScreen() {
    sf::RectangleShape backGround(sf::Vector2f(400, 200));
    backGround.setPosition(game->window.getSize().x / 2.0f - 200, game->window.getSize().y / 2.0f - 100);
    backGround.setFillColor(sf::Color(100, 149, 237)); // Dodger Blue

    sf::Text gameoverText("Game over!", game->font, 40);
    gameoverText.setPosition(game->window.getSize().x / 2.0f - gameoverText.getGlobalBounds().width / 2.0f, game->window.getSize().y / 2.0f - 70);
    gameoverText.setFillColor(sf::Color::White);

    //Button continueButton(window.getSize().x / 2.0f - 50, window.getSize().y / 2.0f + 30, 125, 45, "Try again", font);
    //if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButton.IsMouseOver(window)) {
    //    ResetLevel();
    //}

    game->window.draw(backGround);
    game->window.draw(gameoverText);
    //continueButton.Draw(window);
}

GameState_LevelMode::GameState_LevelMode(Game* game) : player(game->window),
        scoreDisplay(std::to_string(player.score), game->font, 24),
        //deltaTimeClock(),
        gameStatus(Running),
        levelDisplay("Level " + std::to_string(currentLevel + 1), game->font, 24)
{
    this->game = game;
    scoreDisplay.setPosition(sf::Vector2f(float(game->windowWidth / 2), 5));
    levelDisplay.setPosition(sf::Vector2f(5, 5));
    createLevels();
    loadGUI();
}