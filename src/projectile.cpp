#include "projectile.hpp"
#include <cmath>

float Projectile::getSpeed() const {
    return speed_;
}

const std::string& Projectile::getType() const {
   return type_;
}

int Projectile::getDamage() const {
    return damage_;
}

sf::Vector2f Projectile::getShootDir() const {
    return shootDirection_;
}

void Projectile::destroy(){
    isDestroyed_ = true;
}
bool Projectile::isDestroyed(){
    return isDestroyed_;
}

bool Projectile::distToTower() {
    sf::Vector2f currPos = getPosition();

    double dist = sqrt(pow((position_.x - currPos.x),2) + pow((position_.y - currPos.y),2));

    if(dist >= maxDistance_)
    {
        return true;
    }
    return false;
}
