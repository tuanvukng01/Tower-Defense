#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <string>
#include "path.hpp"
#include <queue>
#include "player.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp> 
#include <random>

enum class EnemyType {
    Ground,
    Flying,
    Split,
};

class Enemy :public sf::Sprite {
public:

    /**
     * Initialises an enemy
     * @param hp reference to the health of the enemy
     * @param speed reference to the speed of the enemy
     * @param type reference to the enemy type
     * @param money reference to the amount of money the enemy is worth
     * @param waypoints reference to the waypoints for the enemy to take
     *
    */
    Enemy(int hp, int speed, EnemyType type, int money, std::queue<sf::Vector2f> waypoints)
         : hp_(hp), actualSpeed_(speed), speed_(speed), effectiveSpeed_(speed), type_(type), money_(money), waypoints_(waypoints), initialHp_(hp) {
        
        // Random y value of starting pos, gets set as a negative value
        // So enemies spawn outside window and then move in
        //int rand_y = std::rand() % 40; 

        //tries to avoid enemies being on top of eachother
        std::random_device rd;
        std::uniform_int_distribution range(1,40);
        int x = range(rd);
        int y = range(rd);
        setPosition(waypoints_.front() - sf::Vector2f(x,y));
        
        if (!waypoints_.empty()) {
            currentWaypoint_ = waypoints_.front();
        }
        setVelocity();
    }



    ~Enemy() {}
    /**
     * @brief Update function for enemies, updates enemy positions based on movement, and manages/applies status effects
     * 
     **/
    void update(sf::Time time);
    /**
     *
     * @return returns an sf::Vector2f corresponding to the enemies positional centre
     **/
    sf::Vector2f getCenter();
    /**
     * @return returns the enemies location as a sf::Vector2f
     * 
     **/
    sf::Vector2f getLocation();
    /**
     * @return returns boolean on the sate of the enemy, false if alive true if dead
     **/
    bool dead();
     /**
     * @return returns enemy hp
     **/
    int hp();
     /**
     * @return returns enemies initialHP, this is used for the health text, as it displays the enemies health as a fraction over the initial health
     **/
    int initialHp();
      /**
     * @return returns enemies speed
     **/
    float speed();
      /**
     * @return returns the duration of poison status effect
     **/
    int poisonStatus();
    /**
     * @return returns the duration of slowed status effect
     **/
    sf::Time slowedStatus();
      /**
     * @return returns enemy type
     **/
    EnemyType type();
    /**
     * @brief //damages the enemy, takes in a damage value as a parameter, if the damage is higher than the health the enemy is a 
     * automatically killed
     **/
    void takeDamage(int damage); //decreases the hp_ variable and if hp reaches 0 than the enemy is automatically destroyed
    /**
     * @brief kills the enemy, sets dead variable to true
     **/
    void kill();
    /**
     * @brief applies poison status effect to enemies
     **/
    void applyPoison(int stacksOfPoison, int damagePerStack);

    /**
     * @brief applies slowed status effect to enemies
     **/
    void applySlowed(sf::Time duration, float slowCoefficient);

    void slowedDamage();
    /**
     * @brief sets the enemy velocity based on where the current waypoint is
     * 
     **/
    void setVelocity();
     /**
     * @brief checks to see if the enemies current waypoint will be passed, this is determined by the movement variable of the enemy
     * @return returns a bool
     **/
	bool isWaypointPassed(sf::Vector2f movement);
     /**
     * @brief finds a newwaypoint for the enemy, this function goes through the waypoints qeue and sets the current waypoint as the next waypoint in the qeue
     * if waypoints are empty it means the enemy has reached the castle and the enemy is set to state dead
     **/
	void findNewWaypoint();
    /**
     * @return returns waypoints
     **/
    std::queue<sf::Vector2f> getWaypoints();

	void moveEnemy(sf::Vector2f movement);
    /**
     * @return returns the amount of money this enemy provides when killed
     **/
    int getMoney() const;
    /**
     * @brief updates the health text above enemies with the enemies current health
     **/
    void updateHealthText(const sf::Font& font);
    /**
     * @return returns the healthText
     **/
    const sf::Text& getHealthText() const;

private:
    int hp_;

    int initialHp_;
    
    bool dead_= false;

    float speed_;

    float actualSpeed_;

    float effectiveSpeed_;

    sf::Text healthText_;

    EnemyType type_;

    int poison_ = 0; //If poison is larger than 0 that means that the enemy is poisoned
    // the length of time that the enemy is poisoned for depends on how large the poison
    //value is as the number decreases incrimently until 0
    sf::Time slowed_ = sf::Time::Zero; 
    //How much money the player recieves for killing the monster
    int money_;
    //waypoint based movement, the path class provides a queue of waypoints that take the enemies through the path to the end

    sf::Vector2f velocity_;

	std::queue<sf::Vector2f> waypoints_;

	sf::Vector2f currentWaypoint_;

    int direction_; //0 = down, 1= left, 2= right, 3 = up

    int poisonDamage = 0;

    sf::Time poisonTimer_;
    
    float slowCoefficient_ = 0.f;
};

#endif
