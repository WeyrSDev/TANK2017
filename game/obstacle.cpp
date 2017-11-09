#include "obstacle.h"
#include "rand.h"

Obstacle::Obstacle() {
    Load(OBSTACLE_PATH);
    assert(Loaded());
    
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    rect.setSize(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().width));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(GAME_WIDTH/2, GAME_HEIGHT/2);
}
