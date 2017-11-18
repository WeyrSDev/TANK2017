#include "game.h"
#include "stdafx.h"

Game::Game():
    window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "TANK2017"),
    game_state(GameStates::STATE_MENU) {
    LoadResources();
    
    ResetLevel();
    Start();
}

void Game::Start() {
    srand(std::time(0));
    sf::Keyboard::setVirtualKeyboardVisible(true);
    window.setFramerateLimit(60);

    player_array.push_back(player1);
    player_array.push_back(player2);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (game_state == GameStates::STATE_MENU) {

                // Esc while in menu closes the game
                // Press space to select the level
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                    game_state = GameStates::STATE_LEVEL_SELECT;
                }

            } else if (game_state == GameStates::STATE_PLAY) {

                // Press esc while playing to go back to the menu
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    game_state = GameStates::STATE_MENU;
                    ResetLevel();
                }

            } else if (game_state == GameStates::STATE_LEVEL_SELECT) {

                // Press esc while selecting to go back to menu
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    game_state = GameStates::STATE_MENU;
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
                    // Map selection
                    game_map = new Map(1, obstacle, obstacle_array);
                    game_state = GameStates::STATE_PLAY;
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
                    // Map selection
                    game_map = new Map(2, obstacle, obstacle_array);
                    game_state = GameStates::STATE_PLAY;
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
                    // Map selection
                    game_map = new Map(3, obstacle, obstacle_array);
                    game_state = GameStates::STATE_PLAY;
                }

            } else if (game_state == GameStates::STATE_EXIT) {
                window.close();
            }
        }

        switch (game_state) {
            case STATE_MENU:
                TitleScreen(window);
                break;
            case STATE_LEVEL_SELECT:
                LevelSelect(window);
                break;
            case STATE_PLAY:
                GameLoop(window);
                break;
            case STATE_EXIT:
                break;
        }
    }
}

void Game::GameLoop(sf::RenderWindow& window) {
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
            if (Collision::PixelPerfectTest(projectile_array[counter].sprite, obstacle_array[counter2].sprite) && !obstacle_array[counter2].decoration) {
                if (obstacle_array[counter2].destroyable) {
                    obstacle_array[counter2].hp -= projectile_array[counter].attack_damage;
                    projectile_array[counter].alive = false;
                    if (obstacle_array[counter2].hp <= 0) {
                        obstacle_array[counter2].alive = false; // rip
                    }
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

    // Player updates
    player1.Update(elapsed_time, obstacle_array);
    player2.Update(elapsed_time, obstacle_array);

    // Missile creation (SPACE key) player1
    player1.Fire(projectile, projectile_array, Projectile::P1);
    // Missile creation (ENTER key) player2
    player2.Fire(projectile, projectile_array, Projectile::P2);

    // Missile drawing
    counter = 0;
    for (iter = projectile_array.begin(); iter != projectile_array.end(); iter++) {
        projectile_array[counter].Update(elapsed_time);
        // window.draw(projectile_array[counter].rect); // DEBUG
        window.draw(projectile_array[counter].sprite);
        ++counter;
    }

    // Player drawing
    window.draw(player1.sprite);
    window.draw(player2.sprite);

    // Obstacle drawing
    counter = 0;
    for(e_iter = obstacle_array.begin(); e_iter != obstacle_array.end(); e_iter++) {
        obstacle_array[counter].Update(elapsed_time);
        // window.draw(obstacle_array[counter].rect); // DEBUG
        window.draw(obstacle_array[counter].sprite);
        ++counter;
    }

    window.draw(message); // Popup message
    window.display();
}

void Game::TitleScreen(sf::RenderWindow& window) {
    window.clear();

    sf::Time elapsed_time = frame_clock.restart();
    democannon.AutoMove(elapsed_time);
    democannon1.AutoMove(elapsed_time);
    democannon2.AutoMove(elapsed_time);

    democannon.AutoFire(projectile_array);
    democannon1.AutoFire(projectile_array);
    democannon2.AutoFire(projectile_array);

    // Missile drawing
    std::size_t counter = 0;
    for (iter = projectile_array.begin(); iter != projectile_array.end(); iter++) {
        projectile_array[counter].Update(elapsed_time);
        window.draw(projectile_array[counter].sprite);
        ++counter;
    }

    window.draw(democannon.sprite);
    window.draw(democannon1.sprite);
    window.draw(democannon2.sprite);

    window.draw(title);
    window.draw(subtitle);
    window.display();
}

void Game::LevelSelect(sf::RenderWindow& window) {
    window.clear();

    // Map select

    window.draw(levelselect);
    window.draw(level1);
    window.draw(level2);
    window.draw(level3);

    window.display();
}

void Game::ResetLevel() {
    // Clean map
    while (!obstacle_array.empty()) {
        obstacle_array.pop_back();
    }

    while (!projectile_array.empty()) {
        projectile_array.pop_back();
    }

    message.setString("");

    player1.hp = 30;
    player1.angle = 0;
    player1.sprite.setColor(sf::Color(0, 102, 51));
    player1.sprite.setTextureRect(sf::IntRect(0, 0, 60, 40));
    player1.rect.setPosition(32 * 3, 32 * 3);
    player1.rect.setRotation(0);
    player1.forward = sf::Keyboard::W;
    player1.backwards = sf::Keyboard::S;
    player1.left = sf::Keyboard::A;
    player1.right = sf::Keyboard::D;
    player1.fire = sf::Keyboard::Space;

    player2.hp = 30;
    player2.angle = 180;
    player2.sprite.setColor(sf::Color(0, 102, 110));
    player2.sprite.setTextureRect(sf::IntRect(0, 0, 60, 40));
    player2.rect.setPosition(GAME_WIDTH - 32 * 3, GAME_HEIGHT - 32 * 3);
    player2.rect.setRotation(180);
    player2.forward = sf::Keyboard::I;
    player2.backwards = sf::Keyboard::K;
    player2.left = sf::Keyboard::J;
    player2.right = sf::Keyboard::L;
    player2.fire = sf::Keyboard::Return;
}

// Load and setup initial resources
void Game::LoadResources() {
    // Texture loading
    if (!background_texture.loadFromFile(BACKGROUND_PATH)) {
        std::cout << "Error loading texture!" << "\n";
    }
    background_texture.setRepeated(true);
    background.setTexture(background_texture);
    background.setTextureRect(sf::IntRect(0, 0, GAME_WIDTH, GAME_HEIGHT));

    // Font loading
    if (!title_font.loadFromFile(TITLEFONT_PATH)) {
        std::cout << "Error loading title font!" << "\n";
    }
    if (!digital_font.loadFromFile(DIGITALFONT_PATH)) {
        std::cout << "Error loading digital font!" << "\n";
    }
    if (!level_font.loadFromFile(LEVELFONT_PATH)) {
        std::cout << "Error loading levelfont" << "\n";
    }
    if (!banksia_font.loadFromFile(BANKSIA_PATH)) {
        std::cout << "Banksia!" << "\n";
    }

    // Setup democannon (Title screen cannons)
    democannon.sprite.setColor(sf::Color(0, 102, 51));
    democannon.rect.setPosition(GAME_WIDTH/6, GAME_HEIGHT/2 + GAME_HEIGHT/4);
    democannon.sprite.setScale(1.5f, 1.5f);
    democannon.shot_delay = 4.7f;

    democannon1.sprite.setColor(sf::Color(0, 90, 3));
    democannon1.rect.setPosition(GAME_WIDTH/8, GAME_HEIGHT/2 - GAME_HEIGHT/4);
    democannon1.sprite.setScale(1.5f, 1.5f);
    democannon1.shot_delay = 5.0f;

    democannon2.sprite.setColor(sf::Color(104, 94, 20));
    democannon2.rect.setPosition(GAME_WIDTH/2, GAME_HEIGHT/2);
    democannon2.sprite.setScale(1.5f, 1.5f);
    democannon2.shot_delay = 4.1f;

    // Popup message
    message.setFont(digital_font);
    message.setCharacterSize(100);
    message.setStyle(sf::Text::Bold);
    message.setFillColor(sf::Color(5, 50, 150));
    message.setPosition(GAME_WIDTH/4, GAME_HEIGHT/2);
    // message.setString("DEBUG"); // DEBUG

    // Title message
    title.setFont(title_font);
    title.setString("TANK2017");
    title.setCharacterSize(100);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color(100, 50, 150));
    title.setPosition(GAME_WIDTH/4, GAME_HEIGHT/2 - GAME_HEIGHT/4);

    // Subtitle
    subtitle.setFont(banksia_font);
    subtitle.setString("Barichello");
    subtitle.setCharacterSize(40);
    subtitle.setFillColor(sf::Color(100, 50, 150));
    subtitle.setPosition(GAME_WIDTH/3 + GAME_WIDTH/10, GAME_HEIGHT/2 + GAME_HEIGHT/4);

    // Level select message
    levelselect.setFont(level_font);
    levelselect.setString("- Select level -");
    levelselect.setCharacterSize(65);
    levelselect.setFillColor(sf::Color(10, 100, 20));
    levelselect.setPosition(0, GAME_HEIGHT/2 - GAME_HEIGHT/3);

    // Levels Strings:
    level1.setFont(digital_font);
    level1.setString("Level 1 - Bridge");
    level1.setCharacterSize(40);
    level1.setFillColor(sf::Color(10, 50, 100));
    auto previous_pos = levelselect.getPosition();
    level1.setPosition(previous_pos.x, previous_pos.y + levelselect.getLocalBounds().height + 100);

    level2.setFont(digital_font);
    level2.setString("Level 2 - Fountain");
    level2.setCharacterSize(40);
    level2.setFillColor(sf::Color(10, 50, 100));
    previous_pos = level1.getPosition();
    level2.setPosition(previous_pos.x, previous_pos.y + levelselect.getLocalBounds().height);

    level3.setFont(digital_font);
    level3.setString("Level 3 - ?");
    level3.setCharacterSize(40);
    level3.setFillColor(sf::Color(10, 50, 100));
    previous_pos = level2.getPosition();
    level3.setPosition(previous_pos.x, previous_pos.y + levelselect.getLocalBounds().height);
}
