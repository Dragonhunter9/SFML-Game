#include <random>
#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "Button.h"

static int RandomNumber(const int min, const int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return (distribution(mt));
}

class Level {
private:
    unsigned int levelNumber;
    unsigned int requiredScore;
    float fallingSpeed;
    sf::Vector2i spawnSpeed;
    int bombPossibility;

public:
    Level() : levelNumber(0), requiredScore(1), fallingSpeed(100.0f), spawnSpeed(sf::Vector2i(1, 4)), bombPossibility(4) {}

    Level(const int& number, const int& score, const float& speed, const sf::Vector2i& spawningSpeed, const int& bombSpawnPossibility)
        : levelNumber(number), requiredScore(score), fallingSpeed(speed), spawnSpeed(spawningSpeed), bombPossibility(bombSpawnPossibility) {}

    int GetLevelNumber() const { return levelNumber; };
    unsigned int GetRequiredScore() const { return requiredScore; }
    float GetFallingSpeed() const { return fallingSpeed; }
    sf::Vector2i GetSpawnSpeed() const { return spawnSpeed; }
    int GetBombPossiblity() const { return bombPossibility; }
};

class FallingObject {
protected:
    sf::CircleShape object;

    void Move(const float& deltaTime) {
        if (drawObject) {
            object.move(0.0f, velocity * deltaTime);
        }
    }

    bool TestIfDraw(const sf::RenderWindow& window) {
        if (object.getPosition().y > window.getSize().y - 15 && drawObject == true) {
            drawObject = false;
            return true;
        }
        return false;
    }

public:
    enum ObjectType : unsigned char {
        FallingObj = 0, Coin, Bomb
    };

    virtual ObjectType GetType() const { return ObjectType::FallingObj; }

    FallingObject() : object(10.0f), drawObject(true) {}

    static std::vector<std::unique_ptr<FallingObject>> objects;
    static float velocity;
    static sf::Clock timer;
    static float pauseTime;
    bool drawObject;

    virtual ~FallingObject() = default;

    static void DrawAllObjects(sf::RenderWindow& window) {
        for (const std::unique_ptr<FallingObject>& loopObject : objects) {
            if (loopObject->drawObject) {
                window.draw(loopObject->object);
            }
        }
    }

    static void MoveAllObjects(const float& deltaTime) {
        for (std::unique_ptr<FallingObject>& loopObject : objects) {
            loopObject->Move(deltaTime);
        }
    }

    static void AddPoints(const sf::RenderWindow& window, unsigned int& points) {
        for (const std::unique_ptr<FallingObject>& loopObject : objects) {
            if (loopObject->TestIfDraw(window) && loopObject->GetType() == FallingObject::ObjectType::Bomb) {
                points++;
            }
        }
    }

    sf::FloatRect GetGlobalBounds() const {
        return object.getGlobalBounds();
    }
};

sf::Clock FallingObject::timer;
std::vector<std::unique_ptr<FallingObject>> FallingObject::objects;
float FallingObject::pauseTime;
float FallingObject::velocity = 100.0f;

class Coin : public FallingObject {
public:
    Coin() {
        object.setFillColor(sf::Color::Yellow);
        object.setPosition((float)RandomNumber((int)object.getRadius(), 800 - (int)object.getRadius()), -20.f);
    }

    ObjectType GetType() const override { return ObjectType::Coin; }
};

class Bomb : public FallingObject {
public:
    Bomb() {
        object.setFillColor(sf::Color(128, 128, 128));
        object.setPosition((float)RandomNumber((int)object.getRadius(), 800 - (int)object.getRadius()), -20.f);
    }

    Bomb(const float& playerPos) {
        object.setFillColor(sf::Color(128, 128, 128));
        object.setPosition(playerPos, -20.f);
    }

    ObjectType GetType() const override { return ObjectType::Bomb; }
};

class Player {
private:
    sf::CircleShape ball;
    float velocity;

public:
    unsigned int score = 0;
    unsigned char lives = 3;

    Player(const sf::RenderWindow& window) : ball(10.0f), velocity(300.0f) {
        ball.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    }

    void Draw(sf::RenderWindow& window) const {
        window.draw(ball);
    }

    void Move(const sf::RenderWindow& window, const float& deltaTime) {
        if (ball.getPosition().x > 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                ball.move(-velocity * deltaTime, 0);
            }
        }
        if (ball.getPosition().x + ball.getRadius() * 2 < window.getSize().x) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                ball.move(velocity * deltaTime, 0);
            }
        }
        if (ball.getPosition().y > 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                ball.move(0, -velocity * deltaTime);
            }
        }
        if (ball.getPosition().y + ball.getRadius() * 2 < window.getSize().y) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                ball.move(0, velocity * deltaTime);
            }
        }
    }

    void Collided() {
        for (std::unique_ptr<FallingObject>& loopObject : FallingObject::objects) {
            if (ball.getGlobalBounds().intersects(loopObject->GetGlobalBounds()) && loopObject->drawObject) {
                if (loopObject->GetType() == FallingObject::ObjectType::Coin) {
                    score++;
                    loopObject->drawObject = false;
                    break;
                }
                if (loopObject->GetType() == FallingObject::ObjectType::Bomb) {
                    lives--;
                    loopObject->drawObject = false;
                    break;
                }
            }
        }
    }

    void ResetPosition(const sf::RenderWindow& window) {
        ball.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    }

    void DrawLives(sf::RenderWindow& window) const {
        for (unsigned char i = 0; i < lives; i++) {
            sf::CircleShape live;
            live.setRadius(10.0f);
            live.setFillColor(sf::Color::Red);
            live.setPosition(window.getSize().x - (i * 25.0f + 25.0f), 10);
            window.draw(live);
        }
    }

    sf::Vector2f GetPosition() {
        return ball.getPosition();
    }
};

class Game {
    enum GameState : unsigned char {
        Running = 0, Paused, Won, GameOver
    };

    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window;
    Player player;
    sf::Text scoreDisplay;
    sf::Text levelDisplay;
    sf::Font font;
    sf::Clock deltaTimeClock;
    GameState gameStatus;
    std::vector<Level> levels;
    unsigned int currentLevel;
    int coinSpawnTime;

    tgui::Gui gameGUI;

    void CreateLevels() {
        levels.reserve(5);
        levels.emplace_back(1, 1, 100.0f, sf::Vector2i(1, 5), 4);
        levels.emplace_back(2, 10, 120.0f, sf::Vector2i(1, 4), 4);
        levels.emplace_back(3, 10, 160.0f, sf::Vector2i(1, 3), 3);
        levels.emplace_back(4, 10, 180.0f, sf::Vector2i(0, 3), 3);
        levels.emplace_back(5, 10, 200.0f, sf::Vector2i(0, 2), 2);
        currentLevel = 0;
    }

    void UpdateLevel() {
        if (player.score >= levels[currentLevel].GetRequiredScore()) {
            gameStatus = Won;
            FallingObject::objects.clear();
            currentLevel++;
            player.score = 0;
            player.lives = 3;
            FallingObject::velocity = levels[currentLevel].GetFallingSpeed();
        }
    }

    void NextLevel() {
        gameStatus = Running;
        player.ResetPosition(window);
        deltaTimeClock.restart();
        FallingObject::timer.restart();
    }

    void ResetLevel() {
        FallingObject::objects.clear();
        player.score = 0;
        player.lives = 3;
        player.ResetPosition(window);
        deltaTimeClock.restart();
        FallingObject::timer.restart();

        gameStatus = Running;
    }

    void DisplayPauseScreen() {
        tgui::Gui pauseGUI(window);

        auto button = tgui::Button::create("Pause");
        button->setSize(tgui::Layout2d("50%", "12.5%"));
        button->setPosition(tgui::Layout2d("25%", "43.75%"));
        button->setTextSize(24);

        pauseGUI.add(button);
        pauseGUI.draw();
    }

    void DisplayTGUIWonScreen() {
        if (levels.size() > currentLevel) {
            tgui::Gui wonGUI(window);

            auto panel = tgui::Panel::create();
            panel->setPosition(tgui::Layout2d("25%", "25%"));
            panel->setSize(tgui::Layout2d("50%", "50%"));
            wonGUI.add(panel);

            auto label = tgui::Label::create("Congratulations!\nLevel " + std::to_string(currentLevel) + " completed\n\nPress ENTER to continue");  
            label->setPosition(tgui::Layout2d("25%", "35%"));
            label->setSize(tgui::Layout2d("50%", "50%"));
            label->setTextSize(24);
            label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
            wonGUI.add(label);

            /*auto button = tgui::Button::create("Continue");
            button->setPosition(tgui::Layout2d("50%", "40%"));
            button->setSize(tgui::Layout2d("40%", "10%"));
            button->onPress(NextLevel);
            wonGUI.add(button);*/

            wonGUI.draw();
        }
    }

    void DisplayWonScreen() {
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
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButton.IsMouseOver(window))
                NextLevel();

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

    void DisplayGameOverScreen() {
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

    void DrawGame() {
        window.clear();
        FallingObject::DrawAllObjects(window);
        player.Draw(window);

        window.draw(scoreDisplay);
        window.draw(levelDisplay);
        player.DrawLives(window);

        if (gameStatus == Paused)
            DisplayPauseScreen();
        if (gameStatus == Won)
            DisplayTGUIWonScreen();
        if (gameStatus == GameOver)
            DisplayGameOverScreen();

        gameGUI.draw();

        window.display();
    }

    void UpdateGame() {
        // FallingObject::AddPoints(window, player.score);

        scoreDisplay.setString(std::to_string(player.score));
        levelDisplay.setString("Level " + std::to_string(currentLevel + 1));
        UpdateLevel();

        if (Coin::timer.getElapsedTime().asSeconds() + Coin::pauseTime > coinSpawnTime) {
            coinSpawnTime = RandomNumber(levels[currentLevel].GetSpawnSpeed().x, levels[currentLevel].GetSpawnSpeed().y);
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

    void ProcessEventsAndInputs() {
        sf::Event event;
        while (window.pollEvent(event)) {
            gameGUI.handleEvent(event);

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
            if (levels.size() > currentLevel && gameStatus == Won && (event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Enter))
                NextLevel();
            if (gameStatus == GameOver && (event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Enter))
                ResetLevel();
        }
    }

public:
    Game() : window(sf::VideoMode(windowWidth, windowHeight), "Bounce Ball", sf::Style::Titlebar | sf::Style::Close),
        player(window),
        scoreDisplay(std::to_string(player.score), font, 24),
        deltaTimeClock(),
        gameStatus(Running),
        levelDisplay("Level: " + std::to_string(currentLevel + 1), font, 24),
        gameGUI(window)
    {
        font.loadFromFile("arial.ttf");
        CreateLevels();
        coinSpawnTime = RandomNumber(levels[currentLevel].GetSpawnSpeed().x, levels[currentLevel].GetSpawnSpeed().y);
        tgui::Theme::setDefault("vendor/TGUI/themes/Black.txt");
    }

    void RunGame() {
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
};

int main() {
    Game game;
    game.RunGame();

    return 0;
}