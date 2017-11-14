#include <fstream>

#include "map.h"

void Map::Load(const std::string& filename, unsigned int width, unsigned int height,
    std::map<std::string, Entity>& tile_atlas) {
    
    std::ifstream input_file;
    input_file.open(filename, std::ios::in | std::ios::binary);

    this->width = width;
    this->height = height;

    for (std::size_t pos = 0; pos < width * height; ++pos) {
        Entity entity;
        input_file.read((char*)&entity, sizeof(int));

        tiles.push_back(entity);
    }

    input_file.close();
}

void Map::Save(const std::string& filename) {
    std::ofstream output_file;
    output_file.open(filename, std::ios::out | std::ios::binary);

    // for (auto obstacle : obstacles) {
    //     output_file.write((char*)&entity, sizeof(int));
    // }
    
    output_file.close();
}
