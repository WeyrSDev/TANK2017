#pragma once

#include "stdafx.h"
#include "entity.h"
#include "obstacle.h"

class Player : public Entity {
public:
    Player();
    void Update(sf::Time elapsed_time, const Obstacle& obstacle);
    
    float player_speed = 70.f;
    float attack_damage = 10.f;
    float hp = 30.0f;
    sf::Time last_shot = sf::seconds(0.f);

    sf::Keyboard::Key forward;
    sf::Keyboard::Key backwards;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    
private:
    int counter_walking = 0;
    int rotation_speed = 60;
    sf::Clock _anim_clock;
};
