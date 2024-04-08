#include "Player.hpp"
#include "Game.hpp"

Player::Player(const sf::RenderWindow& window) : character({ 40.0f, 40.0f }), velocity(300.0f), ball(20.0f) {
    character.setOrigin(character.getSize().x / 2, character.getSize().y / 2);
    character.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
}

void Player::Move(const sf::RenderWindow& window, const float deltaTime) {
    /*if (ball.getPosition().x > ball.getRadius()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            ball.move(-velocity * deltaTime, 0);
        }
    }
    if (ball.getPosition().x + ball.getRadius() < window.getSize().x) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            ball.move(velocity * deltaTime, 0); 
        }
    }
    if (ball.getPosition().y > ball.getRadius()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            ball.move(0, -velocity * deltaTime);
        }
    }
    if (ball.getPosition().y + ball.getRadius() < window.getSize().y) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            ball.move(0, velocity * deltaTime); 
        }
    }*/

    if (character.getPosition().x > character.getSize().x / 2) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            character.move(-velocity * deltaTime, 0);
        }
    }
    if (character.getPosition().x + character.getSize().x / 2 < window.getSize().x) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            character.move(velocity * deltaTime, 0);
        }
    }
    if (character.getPosition().y > character.getSize().y / 2) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            character.move(0, -velocity * deltaTime);
        }
    }
    if (character.getPosition().y + character.getSize().y / 2 < window.getSize().y) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            character.move(0, velocity * deltaTime);
        }
    }
}

bool Player::Collided() {
    for (auto& coin : FallingObject::objectsContainer.coins) {
        if (coin.drawObject && character.getGlobalBounds().intersects(coin.GetGlobalBounds())) {
            score++;
            coin.drawObject = false;
            return true;
        }
    }

    for (auto& bomb : FallingObject::objectsContainer.bombs) {
        if (bomb.drawObject && character.getGlobalBounds().intersects(bomb.GetGlobalBounds())) {
            lives--;
            bomb.drawObject = false;
            return true;
        }
    }

    return false;
}

void Player::ResetPosition(const sf::RenderWindow& window) {
    character.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
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
    return character.getPosition();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(character);
}

void Player::setTexture(sf::Texture* texture)
{
    character.setTexture(texture);
}