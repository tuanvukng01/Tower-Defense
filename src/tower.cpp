#include "tower.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include "enemy.hpp"
#include "projectile.hpp"
#include "game.hpp"
#include <cmath>
#include <memory>
#include <iostream>
/**
 * @brief Constructor for abstract tower is used in constructor for derived tower classes.
 * 
 * @param position Determined by constructor of derived tower class
 * @param type Determined by constructor of derived tower class
 * @param baseCost Determined by constructor of derived tower class
 * @param range Determined by constructor of derived tower class
 * @param fireRate Determined by constructor of derived tower class
 * @param damage Determined by constructor of derived tower class
 * @param upgradeCost Determined by constructor of derived tower class
 */
Tower::Tower(sf::Vector2f position, const std::string& type,  int baseCost, float range, sf::Time fireRate,
          int damage, int upgradeCost)
        : type_(type),
        baseCost_(baseCost), 
        range_(range), 
        fireRate_(fireRate), 
        damage_(damage),
        upgradeCost_(upgradeCost), 
        fireTimer_(fireRate),
        currentLvl_(1),
        lockedEnemy_(nullptr), 
        maxLevelReached_(false) {
          setPosition(position);
        }
/**
 * 
 * This method upgrades tower by one level, increases its damage_ member by 1.5 times
 * and sets the maximum level flag to true.
 * 
 * @note If the maximum level has already been reached, this method has no effect
 * 
 */
void Tower::upgradeTower() { 
  if (!isMaxLevelReached()) {
    currentLvl_++;
    damage_ = 1.5 * damage_;
    setMaxLevelFlag();
  }
}

/**
 * @brief Check if the enemy is within the range of the tower
 * 
 * @param enemy A shared pointer to an \c Enemy object passed from calling \c Tower::update method.
 * @return \c true if locking range of the tower is more or equal to distance between the enemy and the tower.
 * @return \c false otherwise.
 */
bool Tower::enemyWithinRange(std::shared_ptr<Enemy> enemy) {
  return range_ >= std::sqrt(std::pow((getPosition().x - enemy->getPosition().x), 2) + std::pow((getPosition().y - enemy->getPosition().y), 2));
}
/**
 * @brief Main logic of tower
 * 
 * First, we check whether currently locked enemy is not \c nullptr, not dead and still within tower's range. If this condition is satisfied nothing else is done. 
 * Otherwise, locked enemy is set to \c nullptr and \c enemies container is iterated through to find the fastest enemy which is within tower's range and alive. If there is no enemies 
 * alive within tower's range, lockedEnemy_ member stays \c nullptr. Otherwise, \c lockedEnemy_ is set to the pointer to the fastest, alive enemy within tower's range.
 * @param enemies List argument passed from calling \c Game::update method.
 * @param time Argument passed from calling \c Game::update method and is used to update \c Tower::fireTimer_.
 */
void Tower::update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) { 
    updateFireTimer(time);
    auto lockedEnemy = getLockedEnemy();
    if (lockedEnemy == nullptr || lockedEnemy->dead() || !enemyWithinRange(lockedEnemy)) {
        setLockedEnemy(nullptr);
        float highestSpeed = 0.f;
        for (std::shared_ptr<Enemy>& enemy : enemies) {
            if (enemyWithinRange(enemy) && !enemy->dead()) {
                if (highestSpeed < enemy->speed()) {
                  highestSpeed = enemy->speed();
                  setLockedEnemy(enemy);
                }
            }
        }
    }
}
/**
 * @brief Increments fireTimer_ by dt
 * 
 * @param dt Time since last frame and is passed from \c Game::update() \e.
 */
void Tower::updateFireTimer(sf::Time &dt) {
  fireTimer_ += dt;
}

