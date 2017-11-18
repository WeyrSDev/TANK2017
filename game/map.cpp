#include "map.h"

Map::Map(std::size_t level_number, Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    switch(level_number) {
        case 1:
            LoadLevel1(obstacle, obstacle_array);
            break;
        case 2:
            LoadLevel2(obstacle, obstacle_array);
            break;
        case 3:
            LoadLevel3(obstacle, obstacle_array);
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
    if (!water_texture.loadFromFile(WATER_SPRITE)) {
        std::cout << "Error loading water texture!" << "\n";
    }
}

void Map::GenerateBorders(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    obstacle.sprite.setTexture(border_texture);
    obstacle.sprite.setColor(sf::Color(100, 100, 100));
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

// >---------- BRIDGE LEVEL ----------<
void Map::LoadLevel1(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    // ----- BRIDGE -----
    obstacle.tiletype = Obstacle::Type::Wall;
    obstacle.sprite.setColor(sf::Color(150, 150, 150)); // Darker color for the rest of the blocks
    obstacle.decoration = false;
    obstacle.destroyable = true;

    // Vertical walls
    // Middle walls
    for (auto i = 32u; i < GAME_HEIGHT/2 - 32 * 2; i+=32) {
        obstacle.rect.setPosition(GAME_WIDTH/2-32 * 2, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2+32 * 2, i);
        obstacle_array.push_back(obstacle);
    }
    for (auto i = GAME_HEIGHT/2 + 32 * 3; i < GAME_HEIGHT-32; i+=32) {
        obstacle.rect.setPosition(GAME_WIDTH/2-32 * 2, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2+32 * 2, i);
        obstacle_array.push_back(obstacle);
    }

    // ----- WATER -----
    obstacle.tiletype = Obstacle::Type::Water;
    obstacle.decoration = false;
    obstacle.destroyable = false;
    obstacle.sprite.setTexture(water_texture);
    // Upper river
    for (auto i = 32u; i < GAME_HEIGHT/2 - 32 * 2; i+=32) {
        obstacle.rect.setPosition(GAME_WIDTH/2-32, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2+32, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2, i);
        obstacle_array.push_back(obstacle);
    }

    // Lower river
    for (auto i = GAME_HEIGHT/2 + 32 * 3; i < GAME_HEIGHT-32; i+=32) {
        obstacle.rect.setPosition(GAME_WIDTH/2-32, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2+32, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2, i);
        obstacle_array.push_back(obstacle);
    }

    // ----- BRICKS -----
    obstacle.tiletype = Obstacle::Type::Wall;
    obstacle.decoration = false;
    obstacle.destroyable = true;
    obstacle.sprite.setTexture(wall_texture);
    obstacle.sprite.setColor(sf::Color(200, 200, 200));

    // Horizontal walls
    for (auto i = 32u * 2; i < GAME_WIDTH - 32 * 2; i+=32) {
        obstacle.rect.setPosition(i, 32);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, GAME_HEIGHT - 32 * 2);
        obstacle_array.push_back(obstacle);
    }

    // Vertical strips
    for (auto i = GAME_HEIGHT/5; i < GAME_HEIGHT - GAME_HEIGHT/5; i+=32) {
        obstacle.rect.setPosition(GAME_WIDTH/2 - 32 * 9, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2 + 32 * 9, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2 - 32 * 10, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH/2 + 32 * 10, i);
        obstacle_array.push_back(obstacle);
    }

    // ----- FOLLIAGE -----
    obstacle.tiletype = Obstacle::Type::Foliage;
    obstacle.decoration = true;
    obstacle.destroyable = false;
    obstacle.sprite.setTexture(leaf_texture);
    obstacle.sprite.setColor(sf::Color(20, 200, 40)); // Green color

    // Vertical strips
    for (auto i = 32u; i < GAME_HEIGHT-32; i+=32) {
        obstacle.rect.setPosition(32, i);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH-32*2, i);
        obstacle_array.push_back(obstacle);
    }

    // Horizontal strips
    for (auto i = 32u * 3; i < GAME_WIDTH/2 - 32*4; i+=32) {
        // Upper left bush
        obstacle.rect.setPosition(i, 32 * 3);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, 32 * 4);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, 32 * 5);
        obstacle_array.push_back(obstacle);

        // Upper right bush
        obstacle.rect.setPosition(GAME_WIDTH-32 - i, 32 * 3);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH-32 - i, 32 * 4);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH-32 - i, 32 * 5);
        obstacle_array.push_back(obstacle);

        // Lower left bush
        obstacle.rect.setPosition(i, GAME_HEIGHT-64 - 32 * 3);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, GAME_HEIGHT-64 - 32 * 4);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, GAME_HEIGHT-64 - 32 * 5);
        obstacle_array.push_back(obstacle);

        // Lower right bush
        obstacle.rect.setPosition(GAME_WIDTH-32 - i, GAME_HEIGHT-64 - 32 * 3);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH-32 - i, GAME_HEIGHT-64 - 32 * 4);
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(GAME_WIDTH-32 - i, GAME_HEIGHT-64 - 32 * 5);
        obstacle_array.push_back(obstacle);
    }

    GenerateBorders(obstacle, obstacle_array);
}

// >---------- FOUNTAIN LEVEL ----------<
// TODO
void Map::LoadLevel2(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    obstacle.rect.setPosition(100, 100);
    obstacle_array.push_back(obstacle);
    GenerateBorders(obstacle, obstacle_array);
}

// >---------- RANDOM LEVEL ----------<
void Map::LoadLevel3(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array) {
    obstacle.tiletype = Obstacle::Type::Wall;
    obstacle.decoration = false;
    obstacle.destroyable = true;
    obstacle.sprite.setTexture(wall_texture);
    obstacle.sprite.setColor(sf::Color(150, 150, 150));

    for (auto i = 32u; i < GAME_WIDTH-32; i+=32) {
        obstacle.rect.setPosition(i, GenerateRandom(GAME_HEIGHT-32*2));
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, GenerateRandom(GAME_HEIGHT-32*2));
        obstacle_array.push_back(obstacle);
        obstacle.rect.setPosition(i, GenerateRandom(GAME_HEIGHT-32*2));
        obstacle_array.push_back(obstacle);
    }

    GenerateBorders(obstacle, obstacle_array);
}
