#include "game.h"
#include "stdafx.h"

void Game::Start() {
    srand(std::time(0));
    sf::Keyboard::setVirtualKeyboardVisible(true);
    sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "TANK2017"); // sf::Style::Fullscreen
    window.setFramerateLimit(60);

    // Texture loading
    sf::Texture background_texture;
    if (!background_texture.loadFromFile(BACKGROUND_PATH)) {
        std::cout << "Error loading texture!" << "\n";
    }
    background_texture.setRepeated(true);
    sf::Sprite background(background_texture);
    background.setTextureRect(sf::IntRect(0, 0, GAME_WIDTH, GAME_HEIGHT));

    // Font loading
    sf::Font font;
    if (!font.loadFromFile(TITLEFONT_PATH)) {
        std::cout << "Error loading font!" << "\n";
    }

    // Popup message
    sf::Text message("", font);
    message.setCharacterSize(100);
    message.setStyle(sf::Text::Bold);
    message.setFillColor(sf::Color(10, 100, 200));
    message.setPosition(GAME_WIDTH/4, 0);
    // message.setString("DEBUG"); // DEBUG

    // Players configuration
    class Player player1;
    player1.rect.setPosition(GAME_WIDTH/4, GAME_HEIGHT/4);
    player1.sprite.setColor(sf::Color(0, 102, 51));
    player1.forward = sf::Keyboard::W;
    player1.backwards = sf::Keyboard::S;
    player1.left = sf::Keyboard::A;
    player1.right = sf::Keyboard::D;
    player1.fire = sf::Keyboard::Space;

    class Player player2;
    player2.rect.setPosition(GAME_WIDTH/4 + 30, GAME_HEIGHT/4);
    // player2.rect.setPosition(GAME_WIDTH*4/5, GAME_HEIGHT*4/5); // Gameplay position
    player2.sprite.setColor(sf::Color(0, 102, 110));
    player2.forward = sf::Keyboard::I;
    player2.backwards = sf::Keyboard::K;
    player2.left = sf::Keyboard::J;
    player2.right = sf::Keyboard::L;
    player2.fire = sf::Keyboard::Return;
    
    std::vector<Player>::const_iterator p_iter;
    std::vector<Player> player_array;
    player_array.push_back(player1);
    player_array.push_back(player2);

    // Projectiles
    class Projectile projectile;
    std::vector<Projectile>::const_iterator iter;
    std::vector<Projectile> projectile_array;

    // Obstacle
    std::vector<Obstacle>::const_iterator e_iter;
    std::vector<Obstacle> obstacle_array;
    
    // Placeholder obstacle generation
    class Obstacle obstacle;
    // Obstacle generation
    for (auto i = 0u; i < 35; ++i) {
        obstacle.rect.setPosition(GenerateRandom(GAME_WIDTH), GenerateRandom(GAME_HEIGHT));
        obstacle_array.push_back(obstacle);
    }

    // Clocks
    sf::Clock frame_clock;
    sf::Clock game_clock;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        sf::Time elapsed_time = frame_clock.restart(); // Frame time

        window.clear();
        window.draw(background);

        // Projectile collision
        std::size_t counter = 0;
        for (iter = projectile_array.begin(); iter != projectile_array.end(); iter++) {
            // Projectile-P1 collision
            if (Collision::PixelPerfectTest(projectile_array[counter].sprite, player1.sprite) && projectile_array[counter].Owner != Projectile::P1) {
                player1.Hit(counter, projectile_array);
                if (player1.hp <= 0) {
                    projectile_array[counter].alive = false;
                    player1.alive = false; // rip
                    message.setString("P2 won!");
                }
                projectile_array.erase(iter);
                break;
            // Projectile-P2 collision
            } else if (Collision::PixelPerfectTest(projectile_array[counter].sprite, player2.sprite) && projectile_array[counter].Owner != Projectile::P2) {
                player2.Hit(counter, projectile_array);
                if (player2.hp <= 0) {
                    projectile_array[counter].alive = false;
                    player2.alive = false; // rip
                    message.setString("P1 won!");
                }
                projectile_array.erase(iter);
                break;
            }

            // Projectile-obstacle collision
            std::size_t counter2 = 0;
            for (e_iter = obstacle_array.begin(); e_iter != obstacle_array.end(); e_iter++) {
                if (Collision::PixelPerfectTest(projectile_array[counter].sprite, obstacle_array[counter2].sprite)) {
                    projectile_array[counter].alive = false;
                    obstacle_array[counter2].hp -= projectile_array[counter].attack_damage;
                    if (obstacle_array[counter2].hp <= 0) {
                        obstacle_array[counter2].alive = false; // rip
                    }
                }
                ++counter2;
            }
            ++counter;
        }

        // Obstacle deletion
        counter = 0;
        for(e_iter = obstacle_array.begin(); e_iter != obstacle_array.end(); e_iter++) {
            if (!obstacle_array[counter].alive) {
                obstacle_array.erase(e_iter);
                break;
            }
            ++counter;
        }

        // Projectile deletion
        counter = 0;
        for(iter = projectile_array.begin(); iter != projectile_array.end(); iter++) {
            if (!projectile_array[counter].alive || projectile_array[counter].rect.getPosition().x > GAME_WIDTH ||
                projectile_array[counter].rect.getPosition().y > GAME_HEIGHT) {
                projectile_array.erase(iter);
                break;
            }
            ++counter;
        }

        // Player rect and sprite updates
        player1.Update(elapsed_time, obstacle_array);
        player2.Update(elapsed_time, obstacle_array);
        // window.draw(player1.rect); // DEBUG
        window.draw(player1.sprite);
        // window.draw(player2.rect); // DEBUG
        window.draw(player2.sprite);

        // Missile creation (SPACE key) player1
        player1.Fire(projectile, projectile_array, Projectile::P1);

        // Missile creation (ENTER key) player2
        player2.Fire(projectile, projectile_array, Projectile::P2);

        // Obstacle drawing
        counter = 0;
        for(e_iter = obstacle_array.begin(); e_iter != obstacle_array.end(); e_iter++) {
            obstacle_array[counter].Update(elapsed_time);
            // window.draw(obstacle_array[counter].rect); // DEBUG
            window.draw(obstacle_array[counter].sprite);
            ++counter;
        }

        // Missile drawing
        counter = 0;
        for (iter = projectile_array.begin(); iter != projectile_array.end(); iter++) {
            projectile_array[counter].Update(elapsed_time);
            // window.draw(projectile_array[counter].rect); // DEBUG
            window.draw(projectile_array[counter].sprite);
            ++counter;
        }

        window.draw(message); // Popup message
        window.display();
    }
}
