#include "stdafx.h"
#include "entity.h"
#include "player.h"
#include "player2.h"
#include "projectile.h"
#include "obstacle.h"

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
    
    // Popup message
    sf::Text message("", font);
    message.setCharacterSize(120);
    message.setStyle(sf::Text::Bold);
    message.setFillColor(sf::Color(10, 100, 200));
    message.setPosition(GAME_WIDTH/2, GAME_HEIGHT/2);

    // Players
    class Player player1;
    player1.sprite.setTexture(p1_texture);
    player1.rect.setPosition(200, 200);
    class Player2 player2;
    player2.sprite.setTexture(p1_texture);
    player2.rect.setPosition(400, 200);

    // Projectiles
    std::vector<Projectile>::const_iterator iter;
    std::vector<Projectile> projectile_array;
    class Projectile projectile1;
    projectile1.sprite.setTexture(flame_texture);

    // Enemies
    std::vector<Obstacle>::const_iterator e_iter;
    std::vector<Obstacle> obstacle_array;
    class Obstacle enemy1;
    enemy1.sprite.setTexture(fox_texture);
    enemy1.rect.setPosition(200, 300);
    
    obstacle_array.push_back(enemy1);

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
            for (e_iter = obstacle_array.begin(); e_iter != obstacle_array.end(); e_iter++) {
                if (projectile_array[counter].rect.getGlobalBounds().intersects(obstacle_array[counter2].rect.getGlobalBounds())) {
                    projectile_array[counter].alive = false;
                    obstacle_array[counter2].hp -= projectile_array[counter].attack_damage;
                    if (obstacle_array[counter2].hp <= 0) {
                        obstacle_array[counter2].alive = false; // rip
                    }
                // P1 collision
                } else if (projectile_array[counter].rect.getGlobalBounds().intersects(player1.rect.getGlobalBounds()) && projectile_array[counter].Owner != Projectile::P1) {
                    player1.alive = false; // rip
                    message.setString("P2 won!");
                // P2 collision
                } else if (projectile_array[counter].rect.getGlobalBounds().intersects(player2.rect.getGlobalBounds()) && projectile_array[counter].Owner != Projectile::P2) {
                    player2.alive = false; // rip
                    message.setString("P1 won!");
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
            if (!projectile_array[counter].alive) {
                projectile_array.erase(iter);
                break;
            }
            ++counter;
        }

        // Player rect and sprite updates
        player1.Update(elapsed_time);
        player2.Update(elapsed_time);
        window.draw(player1.sprite);
        window.draw(player2.sprite);
        window.draw(message);
        
        float shot_delay = 2.f;
        // Missile creation (space key) player1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && game_clock.getElapsedTime().asSeconds() - player1.last_shot.asSeconds() > shot_delay) {
            player1.last_shot = game_clock.getElapsedTime();
            projectile1.angle = player1.angle;

            projectile1.rect.setRotation(projectile1.angle);
            float x = Entity::LinearVelocityX(projectile1.angle);
            float y = Entity::LinearVelocityY(projectile1.angle);

            projectile1.rect.setPosition(player1.rect.getPosition());
            projectile_array.push_back(projectile1);
        }

        // Missile creation (Num0 key) player2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && game_clock.getElapsedTime().asSeconds() - player2.last_shot.asSeconds() > shot_delay) {
            player2.last_shot = game_clock.getElapsedTime();
            projectile1.angle = player2.angle;
            projectile1.Owner = Projectile::P2;

            projectile1.rect.setRotation(projectile1.angle);
            float x = Entity::LinearVelocityX(projectile1.angle);
            float y = Entity::LinearVelocityY(projectile1.angle);

            projectile1.rect.setPosition(player2.rect.getPosition().x + x, player2.rect.getPosition().y + y);
            projectile_array.push_back(projectile1);
        }
        
        // Obstacle creation (Backspace)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            enemy1.rect.setPosition(GenerateRandom(window.getSize().x), GenerateRandom(window.getSize().y));
            obstacle_array.push_back(enemy1);
        }
        
        // Obstacle drawing
        counter = 0;
        for(e_iter = obstacle_array.begin(); e_iter != obstacle_array.end(); e_iter++) {
            obstacle_array[counter].Update(elapsed_time);
            window.draw(obstacle_array[counter].sprite);
            ++counter;
        }
        
        // Missile drawing
        counter = 0;
        for (iter = projectile_array.begin(); iter != projectile_array.end(); iter++) {
            projectile_array[counter].Update(elapsed_time);
            window.draw(projectile_array[counter].rect);
            ++counter;
        }
        
        window.display();
    }
}
