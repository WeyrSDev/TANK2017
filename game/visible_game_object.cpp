#include "visible_game_object.h"

VisibleGameObject::VisibleGameObject():
    loaded{false}
{}

void VisibleGameObject::Load(std::string filename) {
    if (!texture.loadFromFile(filename)) {
        filename = "";
        loaded = false;
    } else {
        filename = filename;
        sprite.setTexture(texture);
        loaded = true;
    }
    // texture.setSmooth(true);
}

void VisibleGameObject::Update(sf::Time elapsed_time) {
    sprite.setPosition(rect.getPosition());
}

bool VisibleGameObject::Loaded() {
    return loaded;
}

