#include "obstacle.h"
#include "rand.h"

Obstacle::Obstacle() {
    rect.setSize(sf::Vector2f(20.f, 20.f));
    rect.setFillColor(sf::Color::Red);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    rect.setPosition(GAME_WIDTH/2, GAME_HEIGHT/2);
}
