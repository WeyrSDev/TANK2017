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
    if (!border_texture.loadFromFile(BORDER_SPRITE)) {
        std::cout << "Error loading border texture!" << "\n";
    }
    if (!wall_texture.loadFromFile(BRICK_SPRITE)) {
        std::cout << "Error loading wall texture!" << "\n";
    }
}

void Map::GenerateBorders(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    obstacle.sprite.setTexture(border_texture);
    obstacle.destroyable = false;
    // Generate vertical border walls
    for (auto i = 0u; i < GAME_HEIGHT; i+=32) {
        obstacle.rect.setPosition(0, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH-32, i);
        obstacle_array.push_back(obstacle);
    }

    // Generate horizontal border walls
    for (auto i = 32u; i < GAME_WIDTH; i+=32) {
        obstacle.rect.setPosition(i, 0);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, GAME_HEIGHT-32);
        obstacle_array.push_back(obstacle);
    }
}

void Map::LoadLevel1(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    // ----- BRICKS -----
    obstacle.decoration = false;
    obstacle.destroyable = true;
    obstacle.sprite.setTexture(wall_texture);
    
    // Vertical walls
    for (auto i = 32u * 6; i < GAME_HEIGHT-32 * 6; i+=32) {
        obstacle.rect.setPosition(32 * 5, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(32 * 6, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH - 32 * 5, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH - 32 * 6, i);
        obstacle_array.push_back(obstacle);
    }

    // ----- FOLLIAGE -----
    obstacle.decoration = true;
    obstacle.sprite.setTexture(leaf_texture);
    
    // Vertical strips
    for (auto i = 32u; i < GAME_HEIGHT-32; i+=32) {
        obstacle.rect.setPosition(32, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH-64, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2-32, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2+32, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2, i);
        obstacle_array.push_back(obstacle);
    }

    // Horizontal strips
    for (auto i = 32u * 3; i < GAME_WIDTH/2 - 32*4; i+=32) {
        obstacle.rect.setPosition(i, 32 * 3);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, 32 * 4);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, 32 * 5);
        obstacle_array.push_back(obstacle);
        
        // Above block mirrored
        obstacle.rect.setPosition(GAME_WIDTH - i, 32 * 3);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH - i, 32 * 4);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH - i, 32 * 5);
        obstacle_array.push_back(obstacle);
        
        obstacle.rect.setPosition(i, GAME_HEIGHT-64 - 32 * 3);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, GAME_HEIGHT-64 - 32 * 4);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, GAME_HEIGHT-64 - 32 * 5);
        obstacle_array.push_back(obstacle);

        // Above block mirrored
        obstacle.rect.setPosition(GAME_WIDTH - i, GAME_HEIGHT-64 - 32 * 3);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH - i, GAME_HEIGHT-64 - 32 * 4);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH - i, GAME_HEIGHT-64 - 32 * 5);
        obstacle_array.push_back(obstacle);
    }

    GenerateBorders(obstacle, obstacle_array);
}

void Map::LoadLevel2(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    obstacle.rect.setPosition(100, 100);
    obstacle_array.push_back(obstacle);
    GenerateBorders(obstacle, obstacle_array);
}
