#include "map.h"

Map::Map(std::size_t level_number, Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    switch(level_number) {
        case 1:
            LoadLevel1(obstacle, obstacle_array);
            break;
        case 2:
            break;
    }

    if (!leaf_texture.loadFromFile(LEAF_SPRITE)) {
        std::cout << "Error loading leaf texture!" << "\n";
    }
}

void Map::GenerateBorders(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    obstacle.destroyable = false;
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
    obstacle.decoration = true;
    obstacle.sprite.setTexture(leaf_texture);
    
    for (auto i = 128u; i < 32 * 10; i+=32) {
        obstacle.rect.setPosition(i, 128);
        obstacle_array.push_back(obstacle);
    }
}

void Map::LoadLevel2(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    GenerateBorders(obstacle, obstacle_array);
    obstacle.rect.setPosition(100, 100);
    obstacle_array.push_back(obstacle);
}
