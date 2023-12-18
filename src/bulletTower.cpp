#include "bulletTower.hpp"
#include "bulletProjectile.hpp"
#include "tower.hpp"
#include <cmath>
#include <memory>

/**
 * 
 * 
 * Uses base Tower constructor.
 */
BulletTower::BulletTower(sf::Vector2f position)
    : Tower(position, "Bullet Tower", 200, 300.f, sf::seconds(1), 15, 300) {}
/**
 * 
 * \c shoot() method calculates the direction towards locked enemy, normalizes it, and creates
 * a BulletProjectile that takes normalized direction, tower's position, damage, and slightly 
 * increased locking range of the tower as arguments. 
 * 
 */
BulletProjectile* BulletTower::shoot() {
    sf::Vector2f direction = getLockedEnemy()->getPosition() - getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = direction / length;
    BulletProjectile* bulletProjectile = new BulletProjectile(normalizedDirection, getPosition(), getDamage(), getRange() + 20);
    return bulletProjectile;
}
