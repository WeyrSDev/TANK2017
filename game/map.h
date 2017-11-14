#pragma once

#include "stdafx.h"
#include "entity.h"

class Map {
public:
    unsigned int width = GAME_WIDTH / 32;
    unsigned int height = GAME_HEIGHT / 32;

    std::vector<Entity> tiles;

    void Load(const std::string& filename, unsigned int width, unsigned int height,
        std::map<std::string, Entity>& tile_atlas);

    void Save(const std::string& filename);

    void Draw(sf::RenderWindow& window, float dt);

    Map() {
        width = 0;
        height = 0;
    }

    Map(const std::string& filename, unsigned int width, unsigned int height,
        std::map<std::string, Entity>& tile_atlas) {
        Load(filename, width, height, tile_atlas);
    }
};
