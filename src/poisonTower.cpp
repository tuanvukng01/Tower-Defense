#include "poisonTower.hpp"
#include <iostream>
/**
 * 
 * 
 * Uses base Tower constructor.
 */
PoisonTower::PoisonTower(sf::Vector2f position)
    : Tower(position, "Poison Tower", 350, 300.f, sf::seconds(2.2), 3, 475) {}
/**
 * 
 * This override for \c update() first updates \c fireTimer_ \e. Then \c lockedEnemies_ container is cleared 
 * and \c lockedEnemy_ is set to \c nullptr \e. After that \c enemies container is iterated through and enemies within
 * tower's range are added to \c lockedEnemies_ container. If at this point \c lockedEnemies_ is not empty, \c lockedEnemy_
 * is set with first pointer in \c std::list<std::shared_ptr<Enemy>> \c lockedEnemies_ \e.
 * 
 */
void PoisonTower::update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) {
    updateFireTimer(time);
    lockedEnemies_.clear();
    setLockedEnemy(nullptr);
    for (std::shared_ptr<Enemy> enemy : enemies) {
        if (enemyWithinRange(enemy)) {
            lockedEnemies_.push_back(enemy);
        }
    }
    if (!lockedEnemies_.empty()) {
        setLockedEnemy(*(lockedEnemies_.begin()));
    }
}
/**
 * Applies the poison effect on every enemy within \c lockedEnemies_ container. 
 * As this method doesn't actually produce a projectile and the poison effect is applied directly on
 * the enemy, return value of this method is always \c nullptr.
 * 
 */
Projectile* PoisonTower::shoot() {
    for (std::shared_ptr<Enemy> enemy : lockedEnemies_) {
        enemy->applyPoison(3, getDamage());
    }
    return nullptr;
}