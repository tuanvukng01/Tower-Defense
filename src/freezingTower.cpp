#include "freezingTower.hpp"
#include <iostream>
/**
 * 
 * 
 * Uses base Tower constructor.
 */
FreezingTower::FreezingTower(sf::Vector2f position)
    : Tower(position, "Freezing Tower", 350, 300.f, sf::seconds(2), 0, 475) {}
/**
 * 
 * This override for \c update() first updates \c fireTimer_ \e. Then \c lockedEnemies_ container is cleared 
 * and \c lockedEnemy_ is set to \c nullptr \e. After that \c enemies container is iterated through and enemies within
 * tower's range are added to \c lockedEnemies_ container. If at this point \c lockedEnemies_ is not empty, \c lockedEnemy_
 * is set with first pointer in \c std::list<std::shared_ptr<Enemy>> \c lockedEnemies_ \e.
 * 
 */
void FreezingTower::update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) {
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
 * Applies the slowing effect on every enemy within \c lockedEnemies_ container. 
 * As this method doesn't actually produce a projectile and the slowing effect is applied directly on
 * the enemy, return value of this method is always \c nullptr.
 * 
 */
Projectile* FreezingTower::shoot() {
    for (std::shared_ptr<Enemy> enemy : lockedEnemies_) {
        enemy->applySlowed(sf::seconds(1.5), slowCoefficient_);
    }
    return nullptr;
}
/**
 * Since FreezingTower is a non-damaging tower class its upgrade has to be overriden. As opposed
 * to base \c upgradeTower() method, upgrade of a FreezingTower increases \c slowCoefficient_ 
 * rather than \c damage_. 
 */
void FreezingTower::upgradeTower() {
    int currentLvl = getCurrentLvl();
    if (currentLvl == 1) {
        setLevel(2);
        slowCoefficient_ = 1.5 * slowCoefficient_;
        setMaxLevelFlag();
    }
}