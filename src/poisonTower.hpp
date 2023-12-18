#ifndef POISON_TOWER
#define POISON_TOWER
#include "tower.hpp"
#include "enemy.hpp"
#include <list>
#include <memory>
/**
 * @class PoisonTower
 * @brief Represents the Poison Tower class.
 * 
 * The PoisonTower is a specialized tower that applies the poison effect on all the enemies within its range. 
 * The poison effect is accomplished by applying it directly on enemies (rather than creating a projectile)
 * and it deals damage over time (x damage every y units of time for the duration of z seconds).
 * The poison effect affects all types of enemies. 
 * 
 */
class PoisonTower : public Tower{
public:
    /** 
     * @brief Constructs a PoisonTower object at the specified position.
     * 
     * @param position The initial position of the PoisonTower (mouse position passed by the caller).
    */
    PoisonTower(sf::Vector2f);
    /**
     * @brief Override of the base class method. 
     * 
     * @param enemies List of enemies passed from calling \c Game::update method.
     * @param time Argument passed from calling \c Game::update method and is used to update \c fireTimer_.
     */    
    void update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) override;
    /**
     * @brief Override of the base class method to that applies the poison effect on enemies.
     * 
     * @return Projectile* This override of shoot() method always returns \c nullptr.
     */    
    Projectile* shoot() override;
private:
    /**
     * @brief List of enemies currently locked by the PoisonTower.
     * 
     * This list holds shared pointers to Enemy objects that the poison effect
     * will be applied to.
     * 
     */
    std::list<std::shared_ptr<Enemy>> lockedEnemies_;
};
#endif 