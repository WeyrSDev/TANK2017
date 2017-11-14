#pragma once

#include "stdafx.h"
#include "visible_game_object.h"

class Entity : public VisibleGameObject {
public:
    float static LinearVelocityX(float angle);
    float static LinearVelocityY(float angle);

    float hp = 0;
    bool alive = true;
    int angle = 0;
};
