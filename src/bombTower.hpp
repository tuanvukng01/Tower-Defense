#ifndef BOMB_TOWER_H
#define BOMB_TOWER_H
#include "tower.hpp"
#include "bombProjectile.hpp"
/**
 * @class BombTower
 * @brief Represents the BombTower class.
 * 
 * The BombTower is a specialized tower that shoots BombProjectile -projectiles. It is derived from
 * the base Tower class and inherits common tower functionalities. Bomb tower can only lock
 * enemies of ground type. BombProjectiles can, however, damage enemies of any type within 
 * explosion range of a bomb projectile (explosion range is dictated solely by bomb projectile objects).
 * 
 */
class BombTower : public Tower {
public:
    /** 
     * @brief Constructs a BombTower object at the specified position.
     * 
     * @param position The initial position of the BombTower (mouse position passed by the caller).
    */
    BombTower(sf::Vector2f);
    /**
     * @brief Override of the base class method. 
     * 
     * @param enemies List of enemies passed from calling \c Game::update method.
     * @param time Argument passed from calling \c Game::update method and is used to update \c fireTimer_.
     */
    void update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) override;
    /**
     * @brief Override of the base class method to produce a BombProjectile.
     * 
     * @return BombProjectile* A pointer to the created BombProjectile object.
     */
    BombProjectile* shoot() override;
};
#endif //BOMB_TOWER