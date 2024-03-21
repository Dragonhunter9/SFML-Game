#include "Game.h"

void Game::CreateLevels() {
    levels.reserve(5);
    levels.emplace_back(1, 10, 100.0f, sf::Vector2i(1, 5), 4);
    levels.emplace_back(2, 10, 120.0f, sf::Vector2i(1, 4), 4);
    levels.emplace_back(3, 10, 160.0f, sf::Vector2i(1, 3), 3);
    levels.emplace_back(4, 10, 180.0f, sf::Vector2i(0, 3), 3);
    levels.emplace_back(5, 10, 200.0f, sf::Vector2i(0, 2), 2);
    currentLevel = 0;
}

void Game::UpdateLevel() {
    if (player.score >= levels[currentLevel].GetRequiredScore()) {
        gameStatus = Won;
        FallingObject::objects.clear();
        currentLevel++;
        player.score = 0;
        player.lives = 3;
        FallingObject::velocity = levels[currentLevel].GetFallingSpeed();
    }
}

void Game::ResetLevel() {
    FallingObject::objects.clear();
    player.score = 0;
    player.lives = 3;
    player.ResetPosition(window);
    deltaTimeClock.restart();
    FallingObject::timer.restart();

    gameStatus = Running;
}

void Game::DisplayPauseScreen() {
    sf::RectangleShape backGround(sf::Vector2f(205, 50));
    backGround.setPosition(window.getSize().x / 2.0f - 100, window.getSize().y / 2.0f - 100);
    backGround.setFillColor(sf::Color::Blue);
    sf::Text pauseText("Game paused", font, 30);
    pauseText.setPosition(window.getSize().x / 2.0f - pauseText.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - pauseText.getGlobalBounds().width / 2.0f);

    window.draw(backGround);
    window.draw(pauseText);
}

void Game::DisplayWonScreen() {
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

        Button continueButton(window.getSize().x / 2.0f - 50, window.getSize().y / 2.0f + 30, 105, 45, "Continue", font);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButton.IsMouseOver(window)) {
            gameStatus = Running;
            player.ResetPosition(window);
            deltaTimeClock.restart();
            FallingObject::timer.restart();
        }

        window.draw(backGround);
        window.draw(wonText);
        window.draw(levelText);
        continueButton.Draw(window);
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

    Button continueButton(window.getSize().x / 2.0f - 50, window.getSize().y / 2.0f + 30, 125, 45, "End Game", font);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButton.IsMouseOver(window)) {
        window.close();
    }

    window.draw(backGround);
    window.draw(wonText);
    window.draw(levelText);
    continueButton.Draw(window);
}

void Game::DisplayGameOverScreen() {
    sf::RectangleShape backGround(sf::Vector2f(400, 200));
    backGround.setPosition(window.getSize().x / 2.0f - 200, window.getSize().y / 2.0f - 100);
    backGround.setFillColor(sf::Color(100, 149, 237)); // Dodger Blue

    sf::Text wonText("Game over!", font, 40);
    wonText.setPosition(window.getSize().x / 2.0f - wonText.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - 70);
    wonText.setFillColor(sf::Color::White);

    Button continueButton(window.getSize().x / 2.0f - 50, window.getSize().y / 2.0f + 30, 125, 45, "Try again", font);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButton.IsMouseOver(window)) {
        ResetLevel();
    }

    window.draw(backGround);
    window.draw(wonText);
    continueButton.Draw(window);
}

void Game::DrawGame() {
    window.clear();
    FallingObject::DrawAllObjects(window);
    player.Draw(window);

    window.draw(scoreDisplay);
    window.draw(levelDisplay);
    player.DrawLives(window);

    if (gameStatus == Paused)
        DisplayPauseScreen();
    if (gameStatus == Won)
        DisplayWonScreen();
    if (gameStatus == GameOver)
        DisplayGameOverScreen();

    window.display();
}

void Game::UpdateGame() {
    // FallingObject::AddPoints(window, player.score);

    scoreDisplay.setString(std::to_string(player.score));
    levelDisplay.setString("Level " + std::to_string(currentLevel + 1));
    UpdateLevel();

    if (Coin::timer.getElapsedTime().asSeconds() + Coin::pauseTime > coinSpawnTime) {
        int coinSpawnTime = RandomNumber(levels[currentLevel].GetSpawnSpeed().x, levels[currentLevel].GetSpawnSpeed().y);
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
        if (event.type == sf::Event::Closed)
            window.close();
        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::P))
        {
            if (gameStatus == Running) {
                gameStatus = Paused;
                FallingObject::pauseTime = FallingObject::timer.getElapsedTime().asSeconds();
            }
            else if (gameStatus == Paused) {
                gameStatus = Running;
                deltaTimeClock.restart();
                FallingObject::timer.restart();
            }
        }
        if (!(levels.size() > currentLevel) && gameStatus == Won && (event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Enter)) {
            gameStatus = Running;
            player.ResetPosition(window);
            deltaTimeClock.restart();
            FallingObject::timer.restart();
        }
        if (gameStatus == GameOver && (event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Enter))
            ResetLevel();
    }
}

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "Bounce Ball", sf::Style::Titlebar | sf::Style::Close),
               player(window),
               scoreDisplay(std::to_string(player.score), font, 24),
               deltaTimeClock(),
               gameStatus(Running),
               levelDisplay("Level: " + std::to_string(currentLevel + 1), font, 24)
{
    font.loadFromFile("arial.ttf");
    CreateLevels();
    coinSpawnTime = RandomNumber(levels[currentLevel].GetSpawnSpeed().x, levels[currentLevel].GetSpawnSpeed().y);
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