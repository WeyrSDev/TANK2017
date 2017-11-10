#pragma once

#include "stdafx.h"
#include "entity.h"

class Obstacle : public Entity {
public:
    Obstacle();

    float hp = 20.f;
    bool alive = true;
};
