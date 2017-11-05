#pragma once

#include "stdafx.h"

class Entity {
public:
    float LinearVelocityX(float angle) {
        if (angle < 0) {
            angle = 360 + angle;
        }
        return (float)std::cos(angle * (3.14159264 / 180.0f));
    }

    float LinearVelocityY(float angle) {
        if (angle < 0){
            angle = 360 + angle;
        }
        return (float)std::sin(angle * (3.14159264 / 180.0f));
    }

    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Text text;

    int angle = 0;
};
