#pragma once

#include "stdafx.h"
#include "entity.h"
#include "player.h"
#include "projectile.h"
#include "obstacle.h"
#include "collision.h"
#include "rand.h"
#include "map.h"

class Game {
public:
    void Start();
    void GameLoop(sf::RenderWindow& window);
    void TitleScreen(sf::RenderWindow& window);
    void LoadResources();

    enum GameStates {
        STATE_MENU,
        STATE_LEVEL_SELECT,
        STATE_PLAY,
        STATE_EXIT
    };

    GameStates game_state = GameStates::STATE_MENU;

    class Player player1;
    class Player player2;
    class Obstacle obstacle;
    class Projectile projectile;

    std::vector<Obstacle>::const_iterator e_iter;
    std::vector<Obstacle> obstacle_array;

    std::vector<Projectile>::const_iterator iter;
    std::vector<Projectile> projectile_array;

    sf::Texture background_texture;
    sf::Sprite background;
    sf::Font font;
    sf::Text message;
    sf::Text title;
    sf::Clock frame_clock;
    sf::Clock game_clock;
};
