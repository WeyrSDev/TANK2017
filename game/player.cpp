#include "player.h"

Player::Player() {
    Load(CHARACTER_PATH);
    assert(Loaded());
    
    rect.setSize(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().width));
    rect.setFillColor(sf::Color::Green);
    //sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    rect.setPosition(GAME_WIDTH/2, GAME_HEIGHT/2);
    
    // Setting origin  to be the center of the sprite
    rect.setOrigin(rect.getGlobalBounds().width/2, rect.getGlobalBounds().height/2);
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
}

void Player::Update(sf::Time elapsed_time, const Obstacle& obstacle) {
    sprite.setPosition(rect.getPosition());
    sprite.setRotation(rect.getRotation());
    
    float move_amount = player_speed * elapsed_time.asSeconds();
    float move_x = LinearVelocityX(angle) * move_amount;
    float move_y = LinearVelocityY(angle) * move_amount;

    if (sf::Keyboard::isKeyPressed(forward)) {
        rect.move(move_x, move_y);
        // sprite.setTextureRect(sf::IntRect(counter_wealking*32, 32 * 2, 32, 32));
    }
    
    if (sf::Keyboard::isKeyPressed(backwards)) {
        rect.move(-move_x, -move_y);
        // sprite.setTextureRect(sf::IntRect(counter_walking*32, 0, 32, 32));
    }

    if (sf::Keyboard::isKeyPressed(left)) {
        if (sf::Keyboard::isKeyPressed(backwards)) {
            rect.rotate(turn_rate * elapsed_time.asSeconds());
        } else {
            rect.rotate(-turn_rate * elapsed_time.asSeconds());
        }
        angle = rect.getRotation();
    }

    if (sf::Keyboard::isKeyPressed(right)) {
        if (sf::Keyboard::isKeyPressed(backwards)) {
            rect.rotate(-turn_rate * elapsed_time.asSeconds());
        } else {
            rect.rotate(turn_rate * elapsed_time.asSeconds());
        }
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

// Update the sprite when the tank gets hit to represent HP
void Player::Hit() {
}
