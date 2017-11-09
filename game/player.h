#pragma once

#include "stdafx.h"
#include "entity.h"
#include "obstacle.h"

class Player : public Entity {
public:
    Player();
    void Update(sf::Time elapsed_time, const Obstacle& obstacle);
    void Hit();
    
    float player_speed = 60.f;
    float attack_damage = 10.f;
    float hp = 30.0f;
    int turn_rate = 40;
    sf::Time last_shot = sf::seconds(0.f);

    sf::Keyboard::Key forward;
    sf::Keyboard::Key backwards;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    
private:
    std::size_t sprite_counter = 0;
    sf::Clock _player_clock;
};
