#pragma once

#include "stdafx.h"
#include "entity.h"

class Obstacle : public Entity {
public:
    Obstacle();
    
    float enemy_speed = 0.5f;
    float hp = 20.f;
    bool alive = true;
    
    std::vector<Obstacle>::const_iterator e_iter;
    std::vector<Obstacle> obstacle_array;

private:

};
