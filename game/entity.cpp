#include "stdafx.h"
#include "entity.h"

Entity::Entity(): 
    _loaded{false} {}

void Entity::Load(std::string filename) {
    if (!texture.loadFromFile(filename)) {
        filename = "";
        _loaded = false;
    } else {
        filename = filename;
        sprite.setTexture(texture);
        _loaded = true;
    }
    // texture.setSmooth(true);
}

void Entity::Update(sf::Time elapsed_time) {
    sprite.setPosition(rect.getPosition());
}

bool Entity::Loaded() {
    return _loaded;
}

float Entity::LinearVelocityX(float angle) {
    if (angle < 0) {
        angle = 360 + angle;
    }
    return (float)std::cos(angle * (3.14159264 / 180.0f));
}

float Entity::LinearVelocityY(float angle) {
    if (angle < 0){
        angle = 360 + angle;
    }
    return (float)std::sin(angle * (3.14159264 / 180.0f));
}
