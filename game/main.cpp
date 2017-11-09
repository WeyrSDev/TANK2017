#include "stdafx.h"
#include "entity.h"
#include "player.h"
#include "projectile.h"
#include "obstacle.h"
#include "collision.h"

#include <iostream>

int main() {
    srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Tank Game"); // sf::Style::Fullscreen
    window.setFramerateLimit(60);

    // Texture and sprites loading
    sf::Texture background_texture;
    if (!background_texture.loadFromFile(BACKGROUND_PATH)) {
        std::cout << "Error loading texture!" << "\n";
        return -1;
    }
    background_texture.setRepeated(true);
    background_texture.setSmooth(true);
    sf::Sprite background(background_texture);
    background.setTextureRect(sf::IntRect(0, 0, GAME_WIDTH, GAME_HEIGHT));

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

    // Players configuration
    class Player player1;
    player1.rect.setPosition(200, 200);
    player1.forward = sf::Keyboard::W;
    player1.backwards = sf::Keyboard::S;
    player1.left = sf::Keyboard::A;
    player1.right = sf::Keyboard::D;

    class Player player2;
    player2.rect.setPosition(400, 200);
    player2.forward = sf::Keyboard::I;
    player2.backwards = sf::Keyboard::K;
    player2.left = sf::Keyboard::J;
    player2.right = sf::Keyboard::L;

    // Projectiles
    std::vector<Projectile>::const_iterator iter;
    std::vector<Projectile> projectile_array;
    class Projectile projectile;

    // Obstacle
    std::vector<Obstacle>::const_iterator e_iter;
    std::vector<Obstacle> obstacle_array;
    class Obstacle obstacle;
    obstacle.rect.setPosition(200, 300);
    
    obstacle_array.push_back(obstacle);

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
                player1.hp -= projectile.attack_damage;
                player1.Hit();
                if (player1.hp <= 0) {
                    projectile_array[counter].alive = false;
                    player1.alive = false; // rip
                    message.setString("P2 won!");
                }
                projectile_array.erase(iter);
                break;
            // Projectile-P2 collision
            } else if (Collision::PixelPerfectTest(projectile_array[counter].sprite, player2.sprite) && projectile_array[counter].Owner != Projectile::P2) {
                player2.hp -= projectile.attack_damage;
                player2.Hit();
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
            if (!projectile_array[counter].alive) {
                projectile_array.erase(iter);
                break;
            }
            ++counter;
        }

        // Player rect and sprite updates
        player1.Update(elapsed_time, obstacle);
        player2.Update(elapsed_time, obstacle);
        window.draw(player1.rect); // Debug
        window.draw(player1.sprite);
        window.draw(player2.sprite);
        
        float shot_delay = 2.f;
        // Missile creation (space key) player1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && game_clock.getElapsedTime().asSeconds() - player1.last_shot.asSeconds() > shot_delay && player1.alive) {
            player1.last_shot = game_clock.getElapsedTime();
            projectile.angle = player1.angle;
            projectile.attack_damage = player1.attack_damage;
            projectile.Owner = Projectile::P1;

            projectile.rect.setRotation(projectile.angle);
            float x = Entity::LinearVelocityX(projectile.angle);
            float y = Entity::LinearVelocityY(projectile.angle);

            projectile.rect.setPosition(player1.sprite.getPosition());
            projectile_array.push_back(projectile);
        }

        // Missile creation (Num0 key) player2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && game_clock.getElapsedTime().asSeconds() - player2.last_shot.asSeconds() > shot_delay && player2.alive) {
            player2.last_shot = game_clock.getElapsedTime();
            projectile.angle = player2.angle;
            projectile.attack_damage = player2.attack_damage;
            projectile.Owner = Projectile::P2;

            projectile.rect.setRotation(projectile.angle);
            float x = Entity::LinearVelocityX(projectile.angle);
            float y = Entity::LinearVelocityY(projectile.angle);

            projectile.rect.setPosition(player2.rect.getPosition().x, player2.rect.getPosition().y);
            projectile_array.push_back(projectile);
        }
        
        // Obstacle creation (Backspace)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            obstacle.rect.setPosition(GenerateRandom(window.getSize().x), GenerateRandom(window.getSize().y));
            obstacle_array.push_back(obstacle);
        }
        
        // Obstacle drawing
        counter = 0;
        for(e_iter = obstacle_array.begin(); e_iter != obstacle_array.end(); e_iter++) {
            obstacle_array[counter].Update(elapsed_time);
            window.draw(obstacle_array[counter].rect); // DEBUG
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
