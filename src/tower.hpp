#ifndef TOWER_H
#define TOWER_H
#include <string>
#include <array>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "projectile.hpp"
#include "enemy.hpp"
#include <memory>


class Projectile;
/**
 * @class Tower
 * @brief Represents abstract tower class
 * 
 * The Tower class is a base class for various types of towers, each with its unique characteristics.
 * Towers can lock onto enemies within a specified range, shoot projectiles, and be upgraded to
 * increase their effectiveness. This class acts as a common interface for managing towers and
 * a foundation for derived tower classes.
 * 
 */
class Tower : public sf::Sprite { 
public:                                
    Tower(sf::Vector2f position, const std::string& type,  int baseCost, float range, sf::Time fireRate,
          int damage, int upgradeCost);
    const std::string& getType() const {return type_;}
    const int getBaseCost() const {return baseCost_;}
    sf::Time getFireRate() const {return fireRate_;}
    const float getRange() const {return range_;}
    int getDamage() const {return damage_;}
    std::shared_ptr<Enemy> getLockedEnemy() const {return lockedEnemy_;}
    bool isMaxLevelReached() const {return maxLevelReached_;};
    int getCurrentLvl() const {return currentLvl_;}
    const int getUpgradeCost() const {return upgradeCost_;}; 
    sf::Time getFireTimer() {return fireTimer_;}
    bool enemyWithinRange(std::shared_ptr<Enemy> enemy);
    /**
     * \brief \c shoot() method is pure virtual as different types of towers produce different types 
     * of projectiles (or no projectiles at all as is the case with PoisonTower and FreezingTower).
     * @return Projectile* 
     */
    virtual Projectile* shoot() = 0; 
    /**
     * \brief \c upgradeTower() method is virtual as upgrade logic is same for all types of towers
     * except FreezingTower
     * 
     * \ref FreezingTower
     * 
     */
    virtual void upgradeTower();
    /**
     * @brief \c update() method is virtual as some types of towers use method of the base class.
     * 
     */
    virtual void update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time);
    void updateFireTimer(sf::Time &dt);
    void setLevel(int level) {currentLvl_ = level;}
    void setMaxLevelFlag() {maxLevelReached_ = true;}
    void setLockedEnemy(std::shared_ptr<Enemy> enemy) {lockedEnemy_ = enemy;}
    void resetFireTimer() {fireTimer_ = sf::Time::Zero;}
    /**
     * @param type_ A string representing type of the tower
     * @param baseCost_ The base cost for the type of tower
     * @param range_ The enemy locking range of the tower
     * @param damage_ Damage of the tower that is passed as a parameter to projectile constructor
     * @param currentLvl_ Current level of the tower, initially set 1 and can be upgraded up to level 2
     * @param upgradeCost_ Set at 1.5 * base cost of tower for all types of towers.
     * @param lockedEnemy_ The locked enemy of the tower; initially set to nullptr.
     * @param fireTimer_ Member used to count how much time has passed since last shot. 
     * @param fireRate_ Member that dictates how often tower can shoot projectiles (or apply other effect on enemies).
     * @param maxLevelReached_ Flag used to check whether tower is already at max level.
     */
private:
    const std::string type_;
    const int baseCost_;
    const float range_;
    int damage_; 
    int currentLvl_;
    const int upgradeCost_; 
    std::shared_ptr<Enemy> lockedEnemy_;
    sf::Time fireTimer_;
    sf::Time fireRate_;
    bool maxLevelReached_;
};
#endif //TOWER_H