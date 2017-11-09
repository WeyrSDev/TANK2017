#pragma once

#include "stdafx.h"

class Entity {
public:
    Entity();
    void Load(std::string filename);
    void Update(sf::Time elapsed_time);
    bool Loaded();

    float static LinearVelocityX(float angle);
    float static LinearVelocityY(float angle);

    sf::RectangleShape rect;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Text text;

    float hp = 0;
    bool alive = true;
    int angle = 0;

private:
    bool _loaded;
};
