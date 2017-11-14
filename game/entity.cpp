#include "stdafx.h"
#include "entity.h"

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
