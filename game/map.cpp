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

void Map::GenerateBorders(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    obstacle.destroyable = false;
    obstacle.sprite.setColor(sf::Color(100, 100, 100));
    // Generate vertical border walls
    for (auto i = 0u; i < GAME_HEIGHT; i+=32) {
        obstacle.rect.setPosition(0, i);
        obstacle_array.push_back(obstacle);
    }
    for (auto i = 0u; i < GAME_HEIGHT; i+=32) {
        obstacle.rect.setPosition(GAME_WIDTH-32, i);
        obstacle_array.push_back(obstacle);
    }

    // Generate horizontal border walls
    for (auto i = 32u; i < GAME_WIDTH; i+=32) {
        obstacle.rect.setPosition(i, 0);
        obstacle_array.push_back(obstacle);
    }
    for (auto i = 32u; i < GAME_WIDTH; i+=32) {
        obstacle.rect.setPosition(i, GAME_HEIGHT-32);
        obstacle_array.push_back(obstacle);
    }
}

void Map::LoadLevel1(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    GenerateBorders(obstacle, obstacle_array);
}

void Map::LoadLevel2(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    GenerateBorders(obstacle, obstacle_array);
}
