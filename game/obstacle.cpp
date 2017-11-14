#include "obstacle.h"
#include "rand.h"

Obstacle::Obstacle() {
    Load(WALL_SPRITE);
    assert(Loaded());

    rect.setSize(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().width));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(GAME_WIDTH/2, GAME_HEIGHT/2);
}
