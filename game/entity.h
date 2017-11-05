#pragma once

#include "stdafx.h"

class Entity {
public:
    float static LinearVelocityX(float angle) {
        if (angle < 0) {
            angle = 360 + angle;
        }
        return (float)std::cos(angle * (3.14159264 / 180.0f));
    }

    float static LinearVelocityY(float angle) {
        if (angle < 0){
            angle = 360 + angle;
        }
        return (float)std::sin(angle * (3.14159264 / 180.0f));
    }
    
    void Update(sf::Time elapsed_time) {
        sprite.setPosition(rect.getPosition());
    }

    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Text text;

    float hp = 0;
    bool alive = true;
    int angle = 0;
};
