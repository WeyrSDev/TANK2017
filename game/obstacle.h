#pragma once

#include "stdafx.h"
#include "entity.h"

class Obstacle : public Entity {
public:
    Obstacle();

    float hp = 10.f;
    bool alive = true;
    bool destroyable = true;
};
