#pragma once

#include "stdafx.h"

class VisibleGameObject {
public:
    VisibleGameObject();
    void Load(std::string filename);
    void Update(sf::Time elapsed_time);
    bool Loaded();

    sf::RectangleShape rect;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Text text;
    
    bool loaded;
};
