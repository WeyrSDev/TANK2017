#pragma once

#include "stdafx.h"
#include "entity.h"

class Player : public Entity {
public:
    Player();

    void Update(sf::Time elapsed_time);
    
    float player_speed = 70.f;
    float attack_damage = 10.f;
    sf::Time last_shot = sf::seconds(0.f);
    
private:
    int counter_walking = 0;
    int rotation_speed = 60;
    sf::Clock _anim_clock;
};
