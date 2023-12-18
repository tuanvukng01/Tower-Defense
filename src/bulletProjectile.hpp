#ifndef BULLET_PROJECTILE
#define BULLET_PROJECTILE

#include "projectile.hpp"

/**
 * @brief a projectile that travels in a straight line and can hit only one enemy
*/
class BulletProjectile : public Projectile
{
public:
    BulletProjectile(sf::Vector2f shootDirection, sf::Vector2f position, int damage, float range) 
    : Projectile(shootDirection, position, damage, 500, "bullet", range) {}

    /**
     * @brief Checks if the bullet has hit an enemy.
     * If the bullet's and enemy's sprites intersect, there has been a hit
     * and the bullet causes damage to the enemy.
     * @returns true if bullet has hit an enemy.
     * @param enemy is a reference to an Enemy object
    */
    bool hasHitEnemy(std::shared_ptr<Enemy>& enemy) override;

    /**
     * If the bullet has gone out of range (exceeded its maximum distance), it's destroyed.
     * Otherwise it goes through all enemies in the game to see if it has hit any one. 
     * If it has hit an enemy, the bullet is destroyed and the checking is stopped.
     * If nothing of the before mentioned has happened, the bullet is moved.
     * @param game is a reference to the running game instance
    */
    void update(Game& game) override;

    /**
     * @returns the texture ID of the type this derived class uses.
    */
    Textures::ProjectileID textureType() override { return Textures::Bullet; }

    /**
     * @brief Calculates the rotation angle of the bullet based on its shooting direction
     * !!! what is it used for
    */
    float rotationAngle() const; //this one is used to calculate rotation angle of a projectile.
};


#endif