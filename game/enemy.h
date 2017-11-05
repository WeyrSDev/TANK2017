#pragma once

#include "stdafx.h"
#include "entity.h"

class Enemy : public Entity {
public:
    Enemy();

    void Update();
    void UpdateMovement();
    
    float enemy_speed = 0.5f;
    float attack_damage = 5;
    float hp = 10.f;
    std::size_t movement_length = 100;
    bool alive = true;
    
private:
    sf::Clock _anim_clock;
    std::size_t counter = 0;
    std::size_t counter_walking = 0;

};
