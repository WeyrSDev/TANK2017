#pragma once

#include "stdafx.h"
#include "entity.h"

class Projectile : public Entity {
public:
    Projectile();
    void Update(sf::Time elapsed_time);

    float movement_speed = 1000.0f;
    float attack_damage = 10.0f;
    bool alive = true;
    sf::Clock _projectile_clock;

private:
    sf::Clock _anim_timer;
    std::size_t counter_walking = 0;
};
