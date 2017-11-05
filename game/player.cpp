#include "player.h"

Player::Player() {
    rect.setSize(sf::Vector2f(32.f, 32.f));
    rect.setFillColor(sf::Color::Green);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    rect.setPosition(GAME_WIDTH/2, GAME_HEIGHT/2);
    
    // Setting origin  to be the center of the sprite
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}

void Player::Update() {
    sprite.setPosition(rect.getPosition());
    sprite.setRotation(rect.getRotation());
}

void Player::UpdateMovement(sf::Time elapsed_time) {
    // if (angle > 360) {
    //     angle = angle - 360;
    // }

    float move_amount = player_speed * elapsed_time.asSeconds();
    float move_x = LinearVelocityX(angle) * move_amount;
    float move_y = LinearVelocityY(angle) * move_amount;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        rect.move(move_x, move_y);
        // sprite.setTextureRect(sf::IntRect(counter_wealking*32, 32 * 2, 32, 32));
 
    }
     
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        rect.move(-move_x, -move_y);
        // sprite.setTextureRect(sf::IntRect(counter_walking*32, 0, 32, 32));
 
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rect.rotate(-60 * elapsed_time.asSeconds());
        angle = rect.getRotation();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rect.rotate(60 * elapsed_time.asSeconds());
        angle = rect.getRotation();
    }

    std::cout << angle << "\n"; // Debug

    // Reset animation clock
    if (_anim_clock.getElapsedTime().asSeconds() > 0.25) {
        counter_walking++;
        _anim_clock.restart();
    }

    if (counter_walking == 4) {
        counter_walking = 0;
    }
}
