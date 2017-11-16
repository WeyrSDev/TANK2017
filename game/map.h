#include "stdafx.h"
#include "obstacle.h"

class Map {
public:
    Map(std::size_t level_number, Obstacle& obstacle, std::vector<Obstacle>& obstacle_array);
    
private:
    void GenerateBorders(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array);
    void LoadLevel1(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array);
    void LoadLevel2(Obstacle& obstacle, std::vector<Obstacle>& obstacle_array);

    sf::Texture leaf_texture;
};
