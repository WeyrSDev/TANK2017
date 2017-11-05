#include "enemy.h"
#include "rand.h"

Enemy::Enemy() {
    rect.setSize(sf::Vector2f(20.f, 20.f));
    rect.setFillColor(sf::Color::Red);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    rect.setPosition(GAME_WIDTH/2, GAME_HEIGHT/2);
}

void Enemy::Update() {
    sprite.setPosition(rect.getPosition());
}

void Enemy::UpdateMovement() {
    // switch(direction) {
    //     case Up:
    //         rect.move(0, -enemy_speed);
    //         sprite.setTextureRect(sf::IntRect(counter_walking*32, 32 * 2, 32, 32));
    //         break;
    //     case Down:
    //         rect.move(0, enemy_speed);
    //         sprite.setTextureRect(sf::IntRect(counter_walking*32, 0, 32, 32));
    //         break;
    //     case Left:
    //         rect.move(-enemy_speed, 0);
    //         sprite.setTextureRect(sf::IntRect(counter_walking*32, 32 * 3, 32, 32));
    //         break;
    //     case Right:
    //         rect.move(enemy_speed, 0);
    //         sprite.setTextureRect(sf::IntRect(counter_walking*32, 32 * 1, 32, 32));
    //         break;
    //     default:
    //         // Using modulo.
    //         sprite.setTextureRect(sf::IntRect(32, 32 * (direction % 3), 32, 32));
    //         break;
    // }

    // Reset animation clock
    if (_anim_clock.getElapsedTime().asSeconds() > 0.20) {
        counter_walking++;
        _anim_clock.restart();
    }

    if (counter_walking == 4) {
        counter_walking = 0;
    }

    // counter++;
    // if (counter >= movement_length) {
    //     std::size_t random = GenerateRandom(5);
    //     switch(random) {
    //         case 0:
    //             direction = Up;
    //             break;
    //         case 1:
    //             direction = Down;
    //             break;
    //         case 2:
    //             direction = Left;
    //             break;
    //         case 3:
    //             direction = Right;
    //             break;
    //     }
    //     counter = 0;
    // }
}
