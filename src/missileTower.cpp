#include "missileTower.hpp"
#include "missileProjectile.hpp"
#include "tower.hpp"
#include <cmath>
#include <memory>
/**
 * 
 * @param position The initial position of the MissileTower (mouse position passed by the caller).
 * 
 * Uses base Tower constructor.
 */
MissileTower::MissileTower(sf::Vector2f position)
    : Tower(position, "Missile Tower", 200, 1000.0f, sf::seconds(3), 30, 300) {}
/**
 * 
 * shoot() method creates a MissileProjectile that takes tower's position, damage and lockedEnemy as arguments.
 * 
 */
MissileProjectile* MissileTower::shoot() {
    MissileProjectile* missileProjectile = new MissileProjectile(getPosition(), getDamage(), getLockedEnemy());
    return missileProjectile;
}
