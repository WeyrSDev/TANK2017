#include "player.h"
#include "collision.h"

Player::Player() {
    Load(PLAYER_PATH);
    assert(Loaded());

    sprite.setTextureRect(sf::IntRect(0, 0, 60, 40));
    rect.setSize(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(GAME_WIDTH/2, GAME_HEIGHT/2);

    // Setting origin to the center of the sprite
    rect.setOrigin(rect.getGlobalBounds().width/2, rect.getGlobalBounds().height/2);
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
}

void Player::Update(sf::Time elapsed_time, std::vector<Obstacle>& obstacle_array) {
    sprite.setPosition(rect.getPosition());
    sprite.setRotation(rect.getRotation());

    if (alive) {
        float move_amount = player_speed * elapsed_time.asSeconds();
        float move_x = LinearVelocityX(angle) * move_amount;
        float move_y = LinearVelocityY(angle) * move_amount;

        // Walls collision
        move_x = CheckOutOfMapX(move_x);
        move_y = CheckOutOfMapY(move_y);

        // Obstacles collision
        std::vector<Obstacle>::const_iterator e_iter;
        std::size_t counter = 0;
        for (e_iter = obstacle_array.begin(); e_iter != obstacle_array.end(); e_iter++) {
            if (Collision::PixelPerfectTest(obstacle_array[counter].sprite, sprite) && !obstacle_array[counter].decoration) {
                move_x = 0;
                move_y = 0;
            }
            ++counter;
        }

        // Movement updates
        if (sf::Keyboard::isKeyPressed(forward)) {
            rect.move(move_x, move_y);
        }
        if (sf::Keyboard::isKeyPressed(backwards)) {
            rect.move(-move_x/2, -move_y/2);
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
    }
    // std::cout << angle << "\n"; // DEBUG
}

// Movement for the title screen tanks
void Player::AutoMove(sf::Time elapsed_time) {
    sprite.setPosition(rect.getPosition());
    sprite.setRotation(rect.getRotation());
    
    float move_amount = player_speed * elapsed_time.asSeconds();
    float move_x = LinearVelocityX(angle) * move_amount;
    float move_y = LinearVelocityY(angle) * move_amount;

    rect.move(move_x, move_y);
    rect.rotate(0.7f * elapsed_time.asSeconds());
    angle = rect.getRotation();

    // Cycle the tank back when it goes out of the screen
    if (rect.getPosition().x > GAME_WIDTH + 200 || rect.getPosition().y > GAME_HEIGHT + 200) {
        rect.setPosition(-200, GenerateRandom(GAME_HEIGHT/2 + GAME_HEIGHT/4));
        rect.setRotation(GenerateRandom(4));
        player_speed = GenerateRandom(10) + 60;
        auto new_color = sf::Color(GenerateRandom(20), 40 + GenerateRandom(100), 40 + GenerateRandom(50));
        sprite.setColor(new_color);
    }
}

// AutoFire for the democannons
void Player::AutoFire(std::vector<Projectile>& projectile_array) {
    if (_player_clock.getElapsedTime().asSeconds() - last_shot.asSeconds() > shot_delay) {
        Projectile projectile;
        last_shot = _player_clock.getElapsedTime();
        projectile.angle = angle;

        projectile.rect.setRotation(projectile.angle);
        float x = Entity::LinearVelocityX(projectile.angle);
        float y = Entity::LinearVelocityY(projectile.angle);

        projectile.rect.setPosition(sprite.getPosition());
        projectile_array.push_back(projectile);
    }
}

// Checks if the tank's sprite is getting out of the screen X axis
float Player::CheckOutOfMapX(float move_x) {
    if (rect.getPosition().x + move_x <= rect.getGlobalBounds().width/2 || rect.getPosition().x + move_x + rect.getGlobalBounds().width/2 >= GAME_WIDTH) {
        return move_x = 0;
    }
    return move_x;
}

// Checks if the tank's sprite is getting out of the screen Y axis
float Player::CheckOutOfMapY(float move_y) {
    if (rect.getPosition().y + move_y <= rect.getGlobalBounds().height/2 || rect.getPosition().y + move_y + rect.getGlobalBounds().height/2 >= GAME_HEIGHT) {
        return move_y = 0;
    }
    return move_y;
}

// Projectile creation
void Player::Fire(Projectile& projectile, std::vector<Projectile>& projectile_array, enum Projectile::Owner owner) {
    if (sf::Keyboard::isKeyPressed(fire) && _player_clock.getElapsedTime().asSeconds() - last_shot.asSeconds() > shot_delay && alive) {
        last_shot = _player_clock.getElapsedTime();
        projectile.angle = angle;
        projectile.attack_damage = attack_damage;
        projectile.Owner = owner;

        projectile.rect.setRotation(projectile.angle);
        float x = Entity::LinearVelocityX(projectile.angle);
        float y = Entity::LinearVelocityY(projectile.angle);

        projectile.rect.setPosition(sprite.getPosition());
        projectile_array.push_back(projectile);
    }
}

// Decreases HP and updates the sprite to represent it
void Player::Hit(std::size_t counter, std::vector<Projectile>& projectile_array) {
    hp -= projectile_array[counter].attack_damage;
    if (sprite_counter < 120) {
        sprite_counter += 40;
    }
    sprite.setTextureRect(sf::IntRect(0, sprite_counter, 60, 40));
}
