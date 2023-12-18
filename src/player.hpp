#ifndef PLAYER
#define PLAYER

#include <string>
#include <list>
#include "enemy.hpp"
#include "tower.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include "resource_container.hpp"

class Tower;
class Enemy;

/**
 * @class Player
 * @brief Class representing the player. 
 * 
 * The class handles player health and money and stores the current level number.
*/
class Player : public sf::Sprite
{
    private:
        int hp_;
        int wallet_;
        int level_;

    public:
        /**
         * @brief Initialises a player with default values
         * @param hp_ is the health points of the player
         * @param wallet_ is how much money the player has
         * @param level_ is the level of the player
        */
        Player() : hp_(500), wallet_(1000), level_(0){}

        ~Player() {}

        /**
         * @returns how much money the player has
        */
        int getWallet() const;

        /**
         * @returns how many health points the player has
        */
        int getHP() const;

        /**
         * @returns the current level of the player
        */
        int getLevel() const;

        /**
         * @brief increases the players level by one
        */
        void levelUp();

        /**
         * @brief adds money to the players wallet
         * @param amount is how much money is to be added
        */
        void addMoney(int amount);

        /**
         * @brief removes money from the players wallet
         * @param cost is how much money is to be removed
        */
        void removeMoney(int cost);

        /**
         * @brief removes health points from the player
         * @param amount is how much hp is to be removed
        */
        void removeHP(int amount);
};

#endif