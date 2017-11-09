#include "projectile.h"

Projectile::Projectile() {
    Load(PROJECTILE_PATH);
    assert(Loaded());
    
    // sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    rect.setSize(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
    rect.setFillColor(sf::Color::Cyan);

    // Setting origin to the center of the sprite
    rect.setOrigin(rect.getGlobalBounds().width/2, rect.getGlobalBounds().height/2);
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
}

void Projectile::Update(sf::Time elapsed_time) {
    sprite.setPosition(rect.getPosition());
    sprite.setRotation(rect.getRotation());
    

    float move_amount = movement_speed * elapsed_time.asSeconds();
    float move_x = LinearVelocityX(angle) * move_amount;
    float move_y = LinearVelocityY(angle) * move_amount;
    
    rect.move(move_x, move_y);
}
