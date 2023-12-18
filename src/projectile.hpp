#ifndef PROJECTILE
#define PROJECTILE

#include "tower.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "resource_container.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class Game;
class Enemy;

/**
 * An abstract class for deriving projectile like, "flying", objects.
*/
class Projectile : public sf::Sprite
{
    private:
        float speed_;
        std::string type_;
        int damage_;
        sf::Vector2f position_; // of tower that created
        float maxDistance_;
        sf::Vector2f shootDirection_;
        bool isDestroyed_;

    public:

        /**
         * @brief Construcs a projectile and sets it's initial position.
         * @param shootDirection is the normalised directional vector used to move the projectile, determined by the creating tower
         * @param position is position of the tower that created the projectile, is used as a starting position
         * @param damage is the amount of damage that the projectile will cause the enemy it hits, determined by the creating tover
         * @param speed is the speed at which the projectile moves, pre-defiened for each derived type
         * @param type is the type of the projectile, pre-defiened for each derived type
         * @param maxDistance is the maximum distance the projectile is allowed to move from it's tower, based on the towers range
        */
        Projectile(sf::Vector2f shootDirection, sf::Vector2f position, int damage, float speed, std::string type, float maxDistance) 
        : shootDirection_(shootDirection), position_(position), damage_(damage), speed_(speed), type_(type), maxDistance_(maxDistance),
        isDestroyed_(false){
            this->setPosition(position_);
        }
        
        /**
         * @brief Destroy the Projectile object
         */
        virtual ~Projectile() {}
        
        /**
         * @returns the speed of the projectile
        */
        float getSpeed() const;

        /**
         * @returns the type of the projectile
        */
        const std::string& getType() const;

        /**
         * @returns the damage of the projectile
        */
        int getDamage() const;

        /**
         * @returns the directional vector of the projectile
        */
        sf::Vector2f getShootDir() const;
        //sf::Vector2f getVelocity() const;

        /**
         * Sets the \p isDestroyed_ flag to true when the projectile has hit an enemy, and fullfilled its purpose,
         * or when it has gone out of range (exceeded its max distance), and needs to be destroyed.
        */
        void destroy();

        /**
         *@brief Returns wheter the projectile is destroyed, and needs to be deleted, or not.
        */
        bool isDestroyed();

       /**
        * @brief Calculates the projectiles distance from the tower that created it.
        * @returns true if the projectile is at, or has exceeded, its maximum distance. False otherwise
       */
        bool distToTower();

       /**
        * @brief checks if the projectile has hit an enemy. Overridden in each derived class.
       */
        virtual bool hasHitEnemy(std::shared_ptr<Enemy>&) = 0;

        /**
         * @brief updates the projectiles state as is defiened in each derived class
        */
       virtual void update(Game&) = 0;

        /**
         * @returns the ID of the texture the projectile type uses
         * The return value is directly hardcoded in derived classes.
        */
       virtual Textures::ProjectileID textureType() = 0;
};
#endif

