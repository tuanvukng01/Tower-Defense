#include "bulletProjectile.hpp"
#include "game.hpp"
#include <cmath>

bool BulletProjectile::hasHitEnemy(std::shared_ptr<Enemy>& enemy) {

    if(this->getGlobalBounds().intersects(enemy->getGlobalBounds())){
        enemy->takeDamage(this->getDamage());
        return true;
    }
    return false;
}
float BulletProjectile::rotationAngle() const {
    return std::atan2(getShootDir().x, getShootDir().y) * (180.f / static_cast<float>(M_PI));
}

void BulletProjectile::update(Game& game){
    float dt = game.getTime().asSeconds();
    //only move the projectile if it hasn't collided or gone out of range
    if(distToTower()){
        destroy();
        //out of range
    }
    else{
         for(auto enemy : game.enemies_){
            if(hasHitEnemy(enemy)){
                destroy();
                break;
            }
        }
        if(!isDestroyed()){
            this->move(getShootDir().x * getSpeed() * dt, getShootDir().y * getSpeed() * dt);
        }
    }
}