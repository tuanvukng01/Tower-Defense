#include "menu.hpp"
#include "bombTower.hpp"
#include "bulletTower.hpp"
#include "missileTower.hpp"
#include "freezingTower.hpp"
#include "poisonTower.hpp"
#include <string>
#include <stdio.h>
#include <algorithm>

#define TOWER_WIDTH_HALF 15
#define TOWER_HEIGHT_HALF 25

// Draws all the buttons in the menu
void Menu::draw(sf::RenderWindow& window) {
    window.draw(bg_);
    for (auto button : buttons_) {
        window.draw(button);
        window.setVerticalSyncEnabled(true);//this should help with the major screen tearing
        window.draw(button.getLabel());
    }

    for (auto text : texts_) {
        window.draw(text);
    }
}

// Iterates through the buttons in the menu and checks if something is clicked
// Chooses action based on button type
void Menu::checkButtons(Game* game) {
    for (auto button : buttons_) {
        if (button.isClicked((sf::Vector2f) sf::Mouse::getPosition(game->window_))) {

            switch (button.getAction())
            {
            case Actions::Tower1:
            {
                std::shared_ptr<BombTower> new_bomb = std::make_shared<BombTower>((sf::Vector2f) sf::Mouse::getPosition(game->window_));
                new_bomb->setTexture(game->tower_textures_.get(Textures::BombTower));
                newTower(new_bomb, game);
                break;
            }
            case Actions::Tower2:
            {
                std::shared_ptr<BulletTower> new_bullet = std::make_shared<BulletTower>((sf::Vector2f) sf::Mouse::getPosition(game->window_));
                new_bullet->setTexture(game->tower_textures_.get(Textures::BulletTower));
                newTower(new_bullet, game);
                break;
            }
            case Actions::Tower3:
            {
                std::shared_ptr<MissileTower> new_missile = std::make_shared<MissileTower>((sf::Vector2f) sf::Mouse::getPosition(game->window_));
                new_missile->setTexture(game->tower_textures_.get(Textures::MissileTower));
                newTower(new_missile, game);
                break;
            }
            case Actions::Tower4:
            {
                std::shared_ptr<FreezingTower> new_freezing = std::make_shared<FreezingTower>((sf::Vector2f) sf::Mouse::getPosition(game->window_));
                new_freezing->setTexture(game->tower_textures_.get(Textures::FreezingTower));
                newTower(new_freezing, game);
                break;
            }
            case Actions::Tower5:
            {
                std::shared_ptr<PoisonTower> new_poison = std::make_shared<PoisonTower>((sf::Vector2f) sf::Mouse::getPosition(game->window_));
                new_poison->setTexture(game->tower_textures_.get(Textures::PoisonTower));
                newTower(new_poison, game);
                break;
            }            

            // If the button upgrade is pressed, there is already a upgrade menu in existence
            // And the tower which we want to upgrade is known
            case Actions::Upgrade:
            {
                // Check that there is enough money for upgrading
                int upgradecost = game->activeTower_->getUpgradeCost();
                if (game->player_.getWallet() >= upgradecost) {
                    // Check that max level is not reached
                    if (!game->activeTower_->isMaxLevelReached()){
                        // Remove money and upgrade
                        game->player_.removeMoney(upgradecost);
                        game->activeTower_->upgradeTower();
                        // Update texts of current damage and level
                        texts_.front().setString("Level: " + std::to_string(game->activeTower_->getCurrentLvl()));
                        texts_.back().setString("Damage: " + std::to_string(game->activeTower_->getDamage()));
                    }
                }
                break;
            }
            case Actions::Close:
            {
                //game->alternativeMenu_ = nullptr;
                game->menuInactive = true;
                game->activeTower_ = nullptr;
                break;
            }
            case Actions::Sell:
            {
                // Add money to player, 75% of tower base cost
                game->player_.addMoney(game->activeTower_->getBaseCost() * 0.75);
                // Find tower and erase it 
                for (auto it = game->towers_.begin(); it != game->towers_.end(); it++) {
                    if (*it == game->activeTower_){
                        game->towers_.erase(it);
                        break;
                    }
                }
                // Remove upgrade menu as the tower does not exist
                game->menuInactive = true;
                game->activeTower_ = nullptr;
                break;
            }
            case Actions::Pause:
            {
                game->paused_ = !game->paused_;
                break;
            }
            case Actions::Level:
            {
                game->paused_ = false;
                game->menuInactive = true;
                break;
            }
            default:
                break;
            }
        }    
        }

}

void Menu::newTower(std::shared_ptr<Tower> tower, Game* game) {
    // if an upgrade menu is open, close it so the change in the 
    // activeTower_ pointer does not break the upgrade menu
    if (game->activeTower_) {
        // unique_ptr handles deletion of old menu
        game->alternativeMenu_ = nullptr;
        game->activeTower_ = nullptr;
    }

    // Set active tower to the new tower being placed
    game->activeTower_ = tower;
    // Set flag which indicates an object is being dragged
    game->dragged_ = true;
    // Color remove area red
    bg_.setFillColor(sf::Color(100, 26, 26, 100));
}

// Creates menu based on the input enum given
void Menu::createMenu(MenuType menu, Game* game) {
    switch (menu)
    {
    case MenuType::Shop:
        {
            // Create background
            bg_ = sf::RectangleShape(sf::Vector2f(100, 800));
            bg_.setPosition(900, 0);
            bg_.setFillColor(sf::Color(0, 26, 26, 100));
            // Create Buttons
            buttons_.push_back(Button(Actions::Tower1, game->tower_textures_.get(Textures::BombTower), sf::Vector2f(920, 40), "300", game->font_));
            buttons_.push_back(Button(Actions::Tower2, game->tower_textures_.get(Textures::BulletTower), sf::Vector2f(920, 100), "200", game->font_));
            buttons_.push_back(Button(Actions::Tower3, game->tower_textures_.get(Textures::MissileTower), sf::Vector2f(920, 160), "200", game->font_));
            buttons_.push_back(Button(Actions::Tower4, game->tower_textures_.get(Textures::FreezingTower), sf::Vector2f(920, 220), "350", game->font_));
            buttons_.push_back(Button(Actions::Tower5, game->tower_textures_.get(Textures::PoisonTower), sf::Vector2f(920, 280), "350", game->font_));
            // This needs a texture or something
            buttons_.push_back(Button(Actions::Pause, game->various_textures_.get(Textures::Pause), sf::Vector2f(900, 700), "pause", game->font_));//uses pause button texture as tower3
            
            std::string money = std::to_string(game->player_.getWallet());
            std::string health = std::to_string(game->player_.getHP());
            std::string level = std::to_string(game->player_.getLevel() + 1);
            sf::Text euro(money + " EUR", game->font_, 20);
            sf::Text hp(health + " HP", game->font_, 20);
            sf::Text lvl("Level: " + level, game->font_, 20);
            lvl.setPosition(900, 550);
            euro.setPosition(900, 600);
            hp.setPosition(900, 650);
            
            texts_.push_back(lvl);
            texts_.push_back(euro);
            texts_.push_back(hp);
            
        }
        break;
    case MenuType::Upgrade:
        {
            // Create upgrade and close buttons
            buttons_.push_back(Button(Actions::Close, game->various_textures_.get(Textures::Continue), sf::Vector2f(500, 700), "Close", game->font_));
            std::string cost = std::to_string(game->activeTower_->getUpgradeCost());
            buttons_.push_back(Button(Actions::Upgrade, game->various_textures_.get(Textures::Upgrade), sf::Vector2f(150, 700), cost, game->font_));
            buttons_.push_back(Button(Actions::Sell, game->various_textures_.get(Textures::Sell), sf::Vector2f(250, 700), "Sell", game->font_));

            // create texts of type current damage and level
            // + operator with string handles conversion
            sf::Text damage(("Damage: " + std::to_string(game->activeTower_->getDamage())), game->font_, 20);
            sf::Text level(("Level: " + std::to_string(game->activeTower_->getCurrentLvl())), game->font_, 20);
            sf::Text type(game->activeTower_->getType(), game->font_, 20);
            
            type.setPosition(30, 700);
            level.setPosition(30, 720);
            damage.setPosition(30, 740);

            // This is a dumb solution, but level is stored first and damage last
            // So they are easy to access if they get updated
            texts_.push_back(level);
            texts_.push_back(type);
            texts_.push_back(damage);
            break;
        }
    case MenuType::Begin:
        {
            buttons_.push_back(Button(Actions::Level, game->various_textures_.get(Textures::Continue), sf::Vector2f(400, 450), "Begin", game->font_));

            sf::Text intro("Welcome to Orcs n Towers\nClick to start the first level!", game->font_, 20);
            intro.setPosition(400, 400);
            texts_.push_back(intro);
            break;
        }
    case MenuType::Level:
        {
            buttons_.push_back(Button(Actions::Level, game->various_textures_.get(Textures::Continue), sf::Vector2f(400, 440), "Next level", game->font_));
            sf::Text intro("Level passed!", game->font_, 20);
            intro.setPosition(400, 400);
            texts_.push_back(intro);
            break;
        }
    default:
        break;
    }
}

void Menu::update(Player& player){
    std::string level = "Level: " + std::to_string(player.getLevel() + 1);
    std::string money = std::to_string(player.getWallet()) + " EUR";
    std::string health = std::to_string(player.getHP()) + " HP";
    texts_[0].setString(level);
    texts_[1].setString(money);
    texts_[2].setString(health);

}

void Menu::drag(Game* game) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        game->activeTower_->setPosition(sf::Mouse::getPosition(game->window_).x, sf::Mouse::getPosition(game->window_).y);
    } else {
        if (game->player_.getWallet() < game->activeTower_->getBaseCost() || !canBePlaced(game)) {
            game->activeTower_ = nullptr;
        } else {
            game->player_.removeMoney(game->activeTower_->getBaseCost());
            game->towers_.push_front(game->activeTower_);
        }
        game->activeTower_ = nullptr;
        game->dragged_ = false;
        bg_.setFillColor(sf::Color(0, 26, 26, 100));
    }
}

void Menu::drawRange(Game* game){
    sf::Vector2f pos = game->activeTower_->getPosition() + sf::Vector2f(TOWER_WIDTH_HALF, TOWER_HEIGHT_HALF);
    float towerRange = game->activeTower_->getRange();
    sf::CircleShape range(towerRange);
    range.setPosition(pos - sf::Vector2f(towerRange, towerRange));
    range.setFillColor(sf::Color(0, 26, 26, 100));
    range.setOutlineColor(sf::Color::White);
    range.setOutlineThickness(1);
    game->window_.draw(range);
}

bool Menu::canBePlaced(Game* game){
    // TODO: Check intersection with path

    sf::FloatRect pos = game->activeTower_->getGlobalBounds();
    // Check intersection with window
    if (!pos.intersects(sf::FloatRect(sf::Vector2f(0, 0), (sf::Vector2f) game->window_.getSize()))) {
        return false;
    }

    // Check intersection with delete area
    if (bg_.getGlobalBounds().intersects(pos)){
        return false;
    }

    // Check intersection with other towers
    for (auto tower : game->towers_) {
        if (pos.intersects(tower->getGlobalBounds())) {
            return false;
        }
    }

    for (auto unBuild : game->map.unBuildable) {
        if (pos.intersects(unBuild)) {
            return false;
        }
    }

    return true;
}