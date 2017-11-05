#include "stdafx.h"
#include "entity.h"
#include "player.h"
#include "projectile.h"
#include "enemy.h"

#include <iostream>

int main() {
    srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Window1"); // sf::Style::Fullscreen
    window.setFramerateLimit(60);

    // Texture and sprites loading
    sf::Texture background_texture;
    if (!background_texture.loadFromFile(BACKGROUND_PATH)) {
        std::cout << "Error loading texture!" << "\n";
        return -1;
    }
    sf::Sprite background(background_texture);

    sf::Texture p1_texture;
    if (!p1_texture.loadFromFile(CHARACTER_PATH)) {
        std::cout << "Error loading player texture!" << "\n";
        return -1;
    }
    sf::Sprite p1_sprite(p1_texture);

    sf::Texture fox_texture;
    if (!fox_texture.loadFromFile(FOX_PATH)) {
        std::cout << "Error loading fox texture!" << "\n";
        return -1;
    }
    sf::Sprite fox_sprite(fox_texture);

    sf::Texture flame_texture;
    if (!flame_texture.loadFromFile(FLAME_PATH)) {
        std::cout << "Error loading flame texture!" << "\n";
        return -1;
    }
    sf::Sprite flame_sprite(flame_texture);

    sf::Font font;
    if (!font.loadFromFile(TITLEFONT_PATH)) {
        std::cout << "Error loading font!" << "\n";
        return -1;
    }
    
    // Title screen
    // sf::Text title("Archer", font);
    // title.setCharacterSize(120);
    // title.setStyle(sf::Text::Bold);
    // title.setFillColor(sf::Color(10, 100, 200));
    // title.setPosition(GAME_WIDTH/2 - 100, GAME_HEIGHT/2 - 100);

    // Player
    class Player player1;
    player1.sprite.setTexture(p1_texture);

    // Projectiles
    std::vector<Projectile>::const_iterator iter;
    std::vector<Projectile> projectile_array;
    class Projectile projectile1;
    projectile1.sprite.setTexture(flame_texture);

    // Enemies
    std::vector<Enemy>::const_iterator e_iter;
    std::vector<Enemy> enemy_array;
    class Enemy enemy1;
    enemy1.sprite.setTexture(fox_texture);
    enemy1.rect.setPosition(200, 300);
    enemy_array.push_back(enemy1);

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
            std::size_t counter2 = 0;
            for (e_iter = enemy_array.begin(); e_iter != enemy_array.end(); e_iter++) {
                if (projectile_array[counter].rect.getGlobalBounds().intersects(enemy_array[counter2].rect.getGlobalBounds())) {
                    projectile_array[counter].alive = false;
                    enemy_array[counter2].hp--;
                    if (enemy_array[counter2].hp <= 0) {
                        enemy_array[counter2].alive = false; // rip
                    }
                }
                ++counter2;
            }
            ++counter;
        }

        // Enemies deletion
        counter = 0;
        for(e_iter = enemy_array.begin(); e_iter != enemy_array.end(); e_iter++) {
            if (!enemy_array[counter].alive) {
                enemy_array.erase(e_iter);
                break;
            }
            ++counter;
        }
        
        // Projectile deletion
        counter = 0;
        for(iter = projectile_array.begin(); iter != projectile_array.end(); iter++) {
            if (!projectile_array[counter].alive) {
                projectile_array.erase(iter);
                break;
            }
            ++counter;
        }

        // Player rect and sprite updates
        player1.Update();
        player1.UpdateMovement(elapsed_time);
        // Draw player
        window.draw(player1.sprite);
        //window.draw(title);
        
        // Missile creation (; key)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon) && game_clock.getElapsedTime().asSeconds() - player1.last_shot.asSeconds() > 2.f) {
            player1.last_shot = game_clock.getElapsedTime();
            sf::Vector2f vector16(16, 16); // Centering
            projectile1.rect.setPosition(player1.rect.getPosition() - vector16);
            projectile1.angle = player1.angle;
            projectile_array.push_back(projectile1);
        }
        
        // Enemy creation (Backspace)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            enemy1.rect.setPosition(GenerateRandom(window.getSize().x), GenerateRandom(window.getSize().y));
            enemy_array.push_back(enemy1);
        }
        
        // Enemy drawing
        counter = 0;
        for(e_iter = enemy_array.begin(); e_iter != enemy_array.end(); e_iter++) {
            enemy_array[counter].Update();
            enemy_array[counter].UpdateMovement();
            window.draw(enemy_array[counter].sprite);
            ++counter;
        }
        
        // Missile drawing (Vectors dont have a self destruct timer)
        counter = 0;
        for (iter = projectile_array.begin(); iter != projectile_array.end(); iter++) {
            projectile_array[counter].Update(elapsed_time);
            window.draw(projectile_array[counter].sprite);
            ++counter;
        }
        
        window.display();
    }
}
