#ifndef EXPLOSION
#define EXPLOSION
#include <SFML/Graphics.hpp> 
#include <SFML/System.hpp>
#include <stdio.h>
#define BOMB_SIZE_HALF 24

/**
 * @class Explosion
 * @brief Small class for drawing bomb explosions
 * 
 * @see BombProjectile
*/
class Explosion : public sf::CircleShape {
public:
    /**
     * @brief Constructs an explosion.
     * 
     * @param blastRange Stores the bomb's blast range
     * @param pos The bomb's position
    */
    Explosion(int blastRange, sf::Vector2f pos) : blastRange_(blastRange), done_(false) {
        time_ = sf::seconds(1);
        setPosition(pos.x + BOMB_SIZE_HALF, pos.y + BOMB_SIZE_HALF);
        setRadius(2);
        setOrigin(2, 2);
        setFillColor(sf::Color(255, 64, 0, 150));
    }

    /**
     * @brief Updates the explosion.
     * 
     * Scales the circle and reduces time left. If the time (1 second) is over, 
     * sets the flag done_
     * 
     * @param inputtime Time between frames from Game::getTime()
    */
    void update(sf::Time inputtime) {
        time_ -= inputtime;
        if (time_ < sf::microseconds(0)) {
            done_ = true;
            //std::cout << "The explosion is done" << std::endl;
            return;
        }
        if (time_ >= sf::seconds(0.5)) {
            setScale(getScale().x + 1, getScale().y + 1);
        } else {
            setScale(getScale().x - 1, getScale().y - 1);
        }

    }

    /**
     * @brief Return done_ which tells if the explosion is done.
    */
    bool isDone(){ return done_; }


private:
    sf::Time time_;
    int blastRange_;
    bool done_;

};

#endif