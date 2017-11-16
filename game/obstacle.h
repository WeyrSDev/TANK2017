#pragma once

#include "stdafx.h"
#include "entity.h"

class Obstacle : public Entity {
public:
    Obstacle();

    float hp = 10.f;
    bool alive = true;
    bool decoration = false; // Collision with projectiles
    bool destroyable = true; // Collision with projectiles and player

    enum Type {
        Border, Wall, Water, Foliage
    };

    Type tiletype;
};
