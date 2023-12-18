#ifndef FREEZING_TOWER
#define FREEZING_TOWER
#include "tower.hpp"
#include "enemy.hpp"
#include <list>
#include <memory>
/**
 * @class FreezingTower
 * @brief Represents the Freezing Tower class.
 * 
 * The Freezing Tower is a specialized non-damaging tower that slows down all the enemies within its range. 
 * The slowing effect is accomplished by applying it directly on enemies (rather than creating a projectile). 
 * Slowing effect affects all types of enemies. 
 * 
 */
class FreezingTower : public Tower{
public:
    /** 
     * @brief Constructs a FreezingTower object at the specified position.
     * 
     * @param position The initial position of the FreezingTower (mouse position passed by the caller).
    */
    FreezingTower(sf::Vector2f);
    /**
     * @brief Override of the base class method. 
     * 
     * @param enemies List of enemies passed from calling \c Game::update method.
     * @param time Argument passed from calling \c Game::update method and is used to update \c fireTimer_.
     */
    void update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) override;
    /**
     * @brief Override of the base class method to that applies the slowing effect on enemies.
     * 
     * @return Projectile* This override of shoot() method always returns \c nullptr.
     */    
    Projectile* shoot() override;
    /**
     * @brief Override of the base class upgradeTower() method. 
     * 
     */        
    void upgradeTower() override;
private:
    /**
     * @brief List of enemies currently locked by the FreezingTower.
     * 
     * This list holds shared pointers to Enemy objects that the slowing effect
     * will be applied to.
     * 
     */
    std::list<std::shared_ptr<Enemy>> lockedEnemies_;
    /**
     * @brief Determines the strength of the slowing effect.
     * 
     * The slowCoefficient_ represents the factor by which the movement speed of
     * enemies is reduced when affected by the slowing effect.
     * 
     */    
    float slowCoefficient_ = 0.2;

};
#endif //FREEZING_TOWER