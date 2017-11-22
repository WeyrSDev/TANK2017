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
    Game();
    void Start();
    void GameLoop(sf::RenderWindow& window, sf::Time elapsed_time);
    void TitleScreen(sf::RenderWindow& window, sf::Time elapsed_time);
    void LevelSelect(sf::RenderWindow& window, sf::Time elapsed_time);
    
    void LoadResources();
    void LoadDemoCannons();

    void DeleteDemoCannons();
    void ResetLevel();

    enum GameStates {
        STATE_MENU,
        STATE_LEVEL_SELECT,
        STATE_PLAY,
        STATE_PAUSE,
        STATE_EXIT
    };

    GameStates game_state = GameStates::STATE_MENU;

    Player* player1;
    Player* player2;
    Player* democannon;
    Player* democannon1;
    Player* democannon2;
    Player* democannon3;
    
    Obstacle obstacle;
    Projectile projectile;

    std::vector<Obstacle>::const_iterator e_iter;
    std::vector<Obstacle> obstacle_array;

    std::vector<Projectile>::const_iterator iter;
    std::vector<Projectile> projectile_array;

    std::vector<Player*>::const_iterator p_iter;
    std::vector<Player*> player_array;

    sf::RenderWindow window;
    sf::Texture background_texture;
    sf::Texture snow_texture;
    sf::Sprite background;

    sf::Font title_font;
    sf::Font digital_font;
    sf::Font level_font;
    sf::Font banksia_font;
    sf::Text message;
    sf::Text title;
    sf::Text subtitle;
    sf::Text press_space;
    sf::Text levelselect;
    sf::Text level1;
    sf::Text level2;
    sf::Text level3;

    Map* game_map;

    sf::Clock frame_clock;
    sf::Clock game_clock;
};
