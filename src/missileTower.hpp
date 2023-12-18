#ifndef MISSILE_TOWER
#define MISSILE_TOWER
#include "tower.hpp"
#include "missileProjectile.hpp"
/**
 * @class MissileTower
 * @brief Represents the MissileTower class.
 * 
 * The MissileTower is a specialized tower that shoots MissileProjectile -projectiles. It is derived from
 * the base Tower class and inherits common tower functionalities.
 */
class MissileTower : public Tower {
public:
    /** 
     * @brief Constructs a MissileTower object at the specified position.
     * 
    */
    MissileTower(sf::Vector2f);
    /**
     * @brief Override of the base class method to produce a MissileProjectile.
     * 
     * @return MissileProjectile* A pointer to the created MissileProjectile object.
     */    
    MissileProjectile* shoot() override;
};
#endif