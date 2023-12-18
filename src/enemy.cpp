#include "enemy.hpp"
#include <string>
#include "game.hpp"
#include "player.hpp"
#include <cmath>
#include <memory>
#include <iostream>
#include <iomanip>
#include <sstream>

void Enemy::moveEnemy(sf::Vector2f movement) { 
    this->move(movement);
}

//Update function for enemies, updates enemy positons based on movement, and manages/applies status effects
void Enemy::update(sf::Time time) {
	sf::Vector2f movement = velocity_  * time.asSeconds();
    if (slowed_ > sf::Time::Zero) {
        slowed_ -= time;
        if (slowed_ <= sf::Time::Zero) {
            slowCoefficient_ = 0.f;
        }
        //the actual amount the enemy is slowed will be tweaked, for now it is 0.2 f
        movement -= velocity_ * (slowCoefficient_) * time.asSeconds();
    }
	
	moveEnemy(movement);
	if (isWaypointPassed(movement))
	{
		findNewWaypoint();
		setVelocity();
	}
    if (poison_ > 0) {
        if (poisonTimer_ >= sf::seconds(1)) {
            takeDamage(poisonDamage);
            poisonTimer_ = sf::Time::Zero;
            poison_ -= 1;
        }
        else {
            poisonTimer_ += time;
        }
    }


}
//checks to see if the enemies current waypoint will be passed, this is determined by the movement variable of the enemy,
// returns a bool.
bool Enemy::isWaypointPassed(sf::Vector2f movement) {
    // Check if the enemy has crossed the waypoint's x-coordinate (for horizontal movement)
    if (velocity_.x != 0) {
        if ((velocity_.x > 0 && getCenter().x + movement.x >= currentWaypoint_.x) ||
            (velocity_.x < 0 && getCenter().x + movement.x <= currentWaypoint_.x)) {
            return true;
        }
    }

    // Check if the enemy has crossed the waypoint's y-coordinate (for vertical movement)
    if (velocity_.y != 0) {
        if ((velocity_.y > 0 && getCenter().y + movement.y >= currentWaypoint_.y) ||
            (velocity_.y < 0 && getCenter().y + movement.y <= currentWaypoint_.y)) {
            return true;
        }
    }

    return false;
}

//returns an sf::Vector2f corresponding to the enemies positional center
sf::Vector2f Enemy::getCenter()
{
	sf::Vector2f enemyCenter;
	enemyCenter.x = this->getPosition().x + this->getGlobalBounds().width / 2;
	enemyCenter.y = this->getPosition().y + this->getGlobalBounds().height / 2;

	return enemyCenter;
}

//sets the enemy velocity based on where the current waypoint is
void Enemy::setVelocity() {

    sf::Vector2f distance;
	distance = currentWaypoint_ - getCenter();

	velocity_.x = distance.x * speed_ / fabs(distance.x + distance.y);
	velocity_.y = distance.y * speed_ / fabs(distance.x + distance.y);

	if (fabs(velocity_.x) > fabs(velocity_.y))
	{
		if (velocity_.x > 0)
		{
			velocity_.x = speed_;
			velocity_.y = 0.f;
			direction_ = 2;
		}
		else
		{
			velocity_.x = -speed_;
			velocity_.y = 0.f;
			direction_ = 1;
		}
	}
	else
	{
		if (velocity_.y > 0)
		{
			velocity_.x = 0.f;
			velocity_.y = speed_;
			direction_ = 0;
		}
		else
		{
			velocity_.x = 0.f;
			velocity_.y = -speed_;
			direction_ = 3;
		}
	}

}

//returns the enemies location as a sf::Vector2f
sf::Vector2f Enemy::getLocation() {
    return this->getPosition();
}
//finds a newwaypoint for the enemy, this function goes through the waypoints qeue and sets the current waypoint as the next waypoint in the qeue
//if waypoints are empty it means the enemy has reached the castle and the enemy is set to state dead
void Enemy::findNewWaypoint() {
    if (!waypoints_.empty()) {
        waypoints_.pop();
        if (!waypoints_.empty()) {
            currentWaypoint_ = waypoints_.front();
        } else {
            dead_ = true; // Mark the enemy as dead
        }
    }
}
//updates the health text above enemies with the enemies current health
void Enemy::updateHealthText(const sf::Font& font) {
    std::ostringstream slowedString;
    slowedString << std::fixed << std::setprecision(1) << slowed_.asSeconds();
    /*std::ostringstream poisonString;
    poisonString << std::fixed << std::setprecision(1) << poison_.asSeconds();*/
    healthText_.setFont(font);
    if (poison_ > 0 && slowed_ > sf::Time::Zero) {
        healthText_.setString(std::to_string(hp_)+ "/" + std::to_string(initialHp_) + 
        " [F:" + slowedString.str() + 
        "][P:" + std::to_string(poison_) + "]");
    }
    else if (poison_ > 0) {
        healthText_.setString(std::to_string(hp_)+ "/" + std::to_string(initialHp_) + " [P:" + std::to_string(poison_) + "]");
    }
    else if (slowed_ > sf::Time::Zero) {
        healthText_.setString(std::to_string(hp_)+ "/" + std::to_string(initialHp_) + " [F:" + slowedString.str() + "]");
    }
    else {
        healthText_.setString(std::to_string(hp_)+ "/" + std::to_string(initialHp_));
    }
    healthText_.setCharacterSize(14);
    healthText_.setFillColor(sf::Color::White); 
    sf::FloatRect bounds = getGlobalBounds();
    healthText_.setPosition(bounds.left + bounds.width / 2.0f, bounds.top - 20);
    sf::FloatRect textBounds = healthText_.getLocalBounds();
    healthText_.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
}
//returns the healthText
const sf::Text& Enemy::getHealthText() const {
        return healthText_;
}
//returns waypoints
std::queue<sf::Vector2f> Enemy::getWaypoints() {
    return waypoints_;
}
//returns boolean on the sate of the enemy, false if alive true if dead
bool Enemy::dead() {
    return dead_;
}
//returns enemy hp
int Enemy::hp() {
    return hp_;
}
//returns enemies initialHP, this is used for the health text, as it displays the enemies health as a fraction over the initial health
int Enemy::initialHp() {
    return initialHp_;
}
//returns enemies speed
float Enemy::speed() {
    return speed_;
}
//returns enemy type
EnemyType Enemy::type() {
    return type_;
}
//returns the duration of poison status effect
int Enemy::poisonStatus() {
    return poison_;
}

sf::Time Enemy::slowedStatus() {
    return slowed_;
}
//kills the enemy, sets dead variable to true
void Enemy::kill() {
    if(!dead_) {
        dead_ = true;
    }
}
//damages the enemy, takes in a damage value as a parameter, if the damage is higher than the health the enemy is a
//automatically killed
void Enemy::takeDamage(int damage) {
    if (dead_) {
        return;
    }
    if(damage >= hp_) {
        kill();
        return;
    } else {
        hp_ -= damage;
    }
}
//Applies poison status effect to enemies
void Enemy::applyPoison(int stacksOfPoison, int damage) {
    poison_ = stacksOfPoison;
    poisonDamage = damage;
    poisonTimer_ = sf::seconds(1);
} 

/* void Enemy::poisonDamage() {
    if(poison_ > 0) {
        takeDamage(1);
        poison_-=1;
    }
} */
//applies slowed status effect to enemies 
void Enemy::applySlowed(sf::Time duration, float slowCoefficient) {
    slowed_ = duration;
    slowCoefficient_ = slowCoefficient;
}

/* void Enemy::slowedDamage() {
    if(slowed_ > 0) {
        slowed_-=1;
    } else {
        effectiveSpeed_ = actualSpeed_;
    }
} */ 

// Returns the amount of money this enemy provides when killed
int Enemy::getMoney() const {
    return money_;
}