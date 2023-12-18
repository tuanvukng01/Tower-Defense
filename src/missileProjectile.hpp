#ifndef MISSILE_PROJECTILE
#define MISSILE_PROJECTILE

#include "projectile.hpp"

/**
 * @brief A projectile that targets (follows) a specific enemy
*/
class MissileProjectile : public Projectile
{
private:
    std::shared_ptr<Enemy> targetEnemy_;

public:
    /**
     * Missile does not need a pre-calculated directional vector,
     * as its direction needs to be re-calculated everytime before it moves,
     * hence the \p shootDirection is (0,0).
     * @param targetEnemy is the enemy that the missile is targeting (following).
    */
    MissileProjectile(sf::Vector2f position, int damage, std::shared_ptr<Enemy> targetEnemy) 
    : Projectile(sf::Vector2f(0,0), position, damage, 280.f, "missile", 400), targetEnemy_(targetEnemy) {}

    /**
     * Checks whether the missile has hit its target or not.
     * If the missile's and enemy's sprites intersect, there has been a hit
     * and the missile causes damage to the enemy.
     * @returns True if missile has hit it's target, otherwise false.
     * @param enemy is a reference to an Enemy object, the missiles target.
    */
    bool hasHitEnemy(std::shared_ptr<Enemy>& enemy) override;

    /**
     * Firstly makes sure that the target enemy still exists, if it doesn't the missile is destroyed.
     * If the enemy still exists it checks whether or not the missile has hit it, 
     * if there's been a hit, the missile is destroyed.
     * If the missile has not hit the enemy, it re-calculates its directional vector, 
     * based on its and the target enemy's current positions, and moves towards the target.
     * @param game is a reference to the running game instance.
    */
    void update(Game& game) override;

    /**
     * @returns the texture ID of the type this derived class uses.
    */
    Textures::ProjectileID textureType() override { return Textures::Missile; }
};


#endif