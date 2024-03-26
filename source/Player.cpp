#include "Player.hpp"

Player::Player(const sf::RenderWindow& window) : ball(10.0f), velocity(300.0f) {
    ball.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
}

void Player::Draw(sf::RenderWindow& window) const {
    window.draw(ball);
}

void Player::Move(const sf::RenderWindow& window, const float deltaTime) {
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

void Player::Collided() {
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

void Player::ResetPosition(const sf::RenderWindow& window) {
    ball.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
}

void Player::DrawLives(sf::RenderWindow& window) const {
    for (unsigned char i = 0; i < lives; i++) {
        sf::CircleShape live;
        live.setRadius(10.0f);
        live.setFillColor(sf::Color::Red);
        live.setPosition(window.getSize().x - (i * 25.0f + 25.0f), 10);
        window.draw(live);
    }
}

sf::Vector2f Player::GetPosition() const {
    return ball.getPosition();
}