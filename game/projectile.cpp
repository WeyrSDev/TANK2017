#include "projectile.h"

Projectile::Projectile() {
    rect.setSize(sf::Vector2f(30.f, 30.f));
    rect.setFillColor(sf::Color::Cyan);
    rect.setPosition(0, 0);

    // Setting origin to the center of the sprite
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}

void Projectile::Update(sf::Time elapsed_time) {
    sprite.setPosition(rect.getPosition());
    sprite.setRotation(rect.getRotation());
    
    sprite.setTextureRect(sf::IntRect(counter_walking*32, 32, 32, 32));

    float move_amount = movement_speed * elapsed_time.asSeconds();
    float move_x = LinearVelocityX(angle) * move_amount;
    float move_y = LinearVelocityY(angle) * move_amount;
    
    rect.move(move_x, move_y);

    // Reset animation clock
    if (_anim_timer.getElapsedTime().asSeconds() > 0.20) {
        counter_walking++;
        _anim_timer.restart();
    }

    if (counter_walking == 4) {
        counter_walking = 0;
    }
}
