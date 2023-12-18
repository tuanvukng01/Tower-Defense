#include "bombTower.hpp"
#include "bombProjectile.hpp"
#include "enemy.hpp"
#include <cmath>
#include <memory>
#include <iostream>
/**
 * 
 * 
 * Uses base Tower constructor.
 */
BombTower::BombTower(sf::Vector2f position)
    : Tower(position, "Bomb Tower", 300, 200.0f, sf::seconds(1.5), 15, 450) {}
/**
 * 
 * This override for \c update() is very similar to \c update() method of base Tower class. 
 * The only difference is that it also checks EnemyType of an enemy as BombTower can only lock on 
 * enemies of \c EnemyType::Ground.
 * 
 */
void BombTower::update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) {
    updateFireTimer(time);
    auto lockedEnemy = getLockedEnemy();
    if (lockedEnemy == nullptr || lockedEnemy->dead() || !enemyWithinRange(lockedEnemy)) {
        setLockedEnemy(nullptr);
        float highestSpeed = 0.f;
        for (std::shared_ptr<Enemy>& enemy : enemies) {
            if (enemyWithinRange(enemy) && enemy->type() == EnemyType::Ground && !enemy->dead()) {
                highestSpeed = enemy->speed();
                setLockedEnemy(enemy);
            }
        }
    }   
}
/**
 * 
 * \c shoot() method calculates the direction towards locked enemy, normalizes it, and creates
 * a BombProjectile that takes normalized direction, tower's position, damage, and 
 * locking range of the tower as arguments. 
 * 
 */
BombProjectile* BombTower::shoot() {
    sf::Vector2f direction = getLockedEnemy()->getPosition() - getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = direction / length;
    BombProjectile* bombProjectile = new BombProjectile(normalizedDirection, getPosition(), getDamage(), getRange());
    return bombProjectile;    
}
