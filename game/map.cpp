#include "map.h"

Map::Map(std::size_t level_number, Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    switch(level_number) {
        case 1:
            LoadLevel1(obstacle, obstacle_array);
            break;
        case 2:
            break;
    }
}

void Map::LoadLevel1(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    obstacle.destroyable = false;
    obstacle.sprite.setColor(sf::Color(100, 100, 100));
    for (auto i = 0u; i < GAME_HEIGHT; i += 32) {
        obstacle.rect.setPosition(GAME_WIDTH-32 ,i);
        obstacle_array.push_back(obstacle);
        for (auto i = 0u; i < GAME_HEIGHT; i +=32) {
            obstacle.rect.setPosition(0 ,i);
            obstacle_array.push_back(obstacle);
        }
    }
}

void Map::LoadLevel2(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    
}
