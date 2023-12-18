#include "player.hpp"
#include "resource_container.hpp"

int Player::getWallet() const {
    return wallet_;
}

int Player::getHP() const {
    return hp_;
}

int Player::getLevel() const {
    return level_;
}

void Player::addMoney(int amount) {
    wallet_ += amount;
}

void Player::removeMoney(int cost) {
    wallet_ -= cost;
}

void Player::removeHP(int amount) {
    hp_ -= amount;
}

void Player::levelUp(){
    level_++;
}
