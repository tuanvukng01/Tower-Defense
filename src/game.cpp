#include "game.hpp"
#include "bombTower.hpp"
#include <memory>
#include "path.hpp"
#include "button.hpp"
#include <iostream>

// initialize game object, mainly create window...
Game::Game() : 
        window_(sf::VideoMode(1000, 800), "Orcs n Towers"), 
        levelManager_("../assets/levels.csv", path_, *this, player_),
        path_("../assets/paths.csv") {
    // Set dragging flag
    dragged_ = false;
    paused_ = false;
    std::cout << "game started" << std::endl;

    //issues with reading from file
    if(!levelManager_.readingSuccessfull()){
        return;
    }

    if(!path_.readingSuccessfull()){
        return;
    }
    
    loadTextures();

    // Initialize menus
    shop_ = std::make_unique<Menu>();
    shop_->createMenu(MenuType::Shop, this);
    alternativeMenu_ = nullptr;
    activeTower_ = nullptr;

    //game over text
    gameOverText.setFont(font_);
    gameOverText.setString("Game Over Loser!!");
    gameOverText.setCharacterSize(24);
    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(400, 200);

    //game finished
    gameFinishedText = sf::Text("Congratulations, you completed the game!", font_, 30);
    gameFinishedText.setFillColor(sf::Color::Black);
    gameFinishedText.setStyle(sf::Text::Bold);
    gameFinishedText.setPosition(220, 200);
    //createPath();
    
    path_.makeUnBuildablePath();
    for (auto path : path_.unBuildable) {
        map.unBuildable.push_back(path);
    }
    
    //Draws castle sprite
    sf::Texture& castleTexture = various_textures_.get(Textures::Castle);
    castle_sprite_.setTexture(castleTexture);
    sf::Vector2f castlePosition = sf::Vector2f(path_.wayPoints.back().x - (castle_sprite_.getTexture()->getSize().x/2), path_.wayPoints.back().y - (castle_sprite_.getTexture()->getSize().y/2));
    castle_sprite_.setPosition(castlePosition);
    

    //testEnemy();

    player_ = Player();
};


path& Game::getPath() {
    return path_;
}
// Run main game loop
void Game::run() {
    while (window_.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

// Process inputs, handle closing window
void Game::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;

        case sf::Event::MouseButtonPressed:
            // If statement checks that nothing is being dragged currently
            // if MouseButtonPressed event only happens when button is initially pressed
            // this if statement is unnecessary
            if (!dragged_) {
                shop_->checkButtons(this);
                if (alternativeMenu_) {
                    alternativeMenu_->checkButtons(this);
                }
                if (!dragged_) {
                    checkTowers(); // If no button was pressed check if a tower has been clicked
                }
                break;
            }

        default:
            break;
        }
    }
}

// Call functions necessary for iterating over all objects and updating their states
void Game::update() {
    time_ = clock_.restart();
    

    updateMenus();

    // If the game is paused stop updating
    if (paused_) {
        return;
    }
    if (player_.getHP() <= 0) {
        //game over
        isGameOver_ = true;
        return;
    }

    //game has been completed, should probably do something else than just pause
    //lm update will increase current level by one even after it has run out of waves for the last level
    if(levelManager_.getCurrentLevel() >= levelManager_.getLevelTotal()){
        //paused_ = true;
        isGameFinished_ = true;
        return;
    }

    levelManager_.update();

    for (auto& enemy : enemies_) {
        if (!enemy->dead()) {
            enemy->update(getTime());
            enemy->updateHealthText(font_); // Update health text
        }
    }

    // Pavel: following order of updates is perhaps ok
    for (auto it = enemies_.begin(); it != enemies_.end();) {
        if ((*it)->dead()) {
            //this if statement and the functions inside are used to test the
            //enemy split functionality
            if ((*it)->getWaypoints().empty()) {
                player_.removeHP(250);
                std::cout << "player health: " << player_.getHP() << std::endl;//player hp deduction test (works!!)
            }
            else {
                // Add money to player for successful kill
                player_.addMoney((*it)->getMoney());
            }
            if ((*it)->type() == EnemyType::Split) { //now if the enemy dies because it reached the castle it wont split, otherwise it will
                //I also fixed the split enemies movement
                std::queue<sf::Vector2f> waypoints = (*it)->getWaypoints();
                

                if (!waypoints.empty()) {
                    sf::Vector2f position = (*it)->getCenter();
                    testEnemySplit(position, waypoints);
                }
            
            }
        
            //removes an enemy from the list and subsequently it is destroyed, if the enemy
            //is dead
            it = enemies_.erase(it);
        }
        else {
            //        std::cout << enemies_.size() << std::endl;
            (*it)->update(getTime());
            //if enemy has reached the castle
           //player_.reachedCastle(*it); //this might not work since enemies are dead once they reach the final
            //checkpoint (the castle) may not activate this
            ++it;
        }
    }

    for (auto tower : towers_) {
        tower->update(enemies_, getTime());
        if (tower->getLockedEnemy() != nullptr &&
            tower->getFireTimer() >= tower->getFireRate()) {
                Projectile* newproj = tower->shoot();
                if (newproj != nullptr) {
                    newproj->setTexture(projectile_textures_.get(newproj->textureType()));
                    projectiles_.push_back(newproj);
                }

                tower->resetFireTimer();

            }
    }
    
    //cleans up list while iterating
    for (auto i = projectiles_.begin(); i != projectiles_.end();) {
        (*i)->update(*this);

        if ((*i)->isDestroyed()) {
            delete (*i);
            //erase returns next iterator
            i = projectiles_.erase(i);
        }
        else {
            i++;
        }
    }

    for (auto i = explosions_.begin(); i != explosions_.end();) {
        (*i)->update(getTime());

        if ((*i)->isDone()) {
            delete (*i);
            //erase returns next iterator
            i = explosions_.erase(i);
        }
        else {
            i++;
        }
    }
}
//createPath function used to test the game out, so far the coordinates are
//hardcoded
/*void Game::createPath() {
    path_.addWaypoint(sf::Vector2f(133, 20));
    path_.addWaypoint(sf::Vector2f(133, 400));
    path_.addWaypoint(sf::Vector2f(400, 400));
    path_.addWaypoint(sf::Vector2f(500, 400));
    path_.addWaypoint(sf::Vector2f(500, 200));
    path_.addWaypoint(sf::Vector2f(500, 300));
    path_.addWaypoint(sf::Vector2f(700, 300));
    path_.addWaypoint(sf::Vector2f(700, 500));
    path_.addWaypoint(sf::Vector2f(700, 700));
}*/
// Iterate over objects, render them onto window
void Game::render() {
    window_.clear();
    window_.draw(map);
    for (auto path : path_.unBuildable) {
        sf::RectangleShape rectShape(sf::Vector2f(path.width, path.height));
        rectShape.setPosition(path.left, path.top);
        const sf::Texture& dirtTexture = various_textures_.get(Textures::Dirt);
        rectShape.setTexture(&dirtTexture); 
        window_.draw(rectShape);
    }

    window_.draw(castle_sprite_);

    if (activeTower_) {
        window_.draw(*activeTower_);
    }
    for (auto tower : towers_) {
        window_.draw(*tower);
    }
    for (auto* projectile : projectiles_) {
        window_.draw(*projectile);
    }
    for (auto enemy : enemies_) {
        if (!enemy->dead()) { //added a if statement to check if the enemy is dead, if it is it wont be rendered
            window_.draw(*enemy);
            window_.draw(enemy->getHealthText());
        }

    }
    // NOTE: test
    for (auto* explosion : explosions_) {
        window_.draw(*explosion);
    }

    if (isGameOver_) {
        window_.draw(gameOverText);
    }

    if(isGameFinished_){
        window_.draw(gameFinishedText);
    }

    // If a tower is active draw it's range
    if (activeTower_) {
        shop_->drawRange(this);
    }
    
    // Draw menu items last so they don't get blocked by other stuff
    shop_->draw(window_);
    if (alternativeMenu_) {
        alternativeMenu_->draw(window_);
    }
    window_.display();
}


sf::Time Game::getTime() const {
    return time_;
}

void Game::checkTowers() {
    sf::Vector2f mousepos = (sf::Vector2f)sf::Mouse::getPosition(window_);
    for (auto tower : towers_) {
        if (tower->getGlobalBounds().contains(mousepos)) {
            // This stores the pointer to the tower that the upgrade button
            // Will potentially upgrade
            activeTower_ = tower;
            alternativeMenu_ = std::make_unique<Menu>();
            alternativeMenu_->createMenu(MenuType::Upgrade, this);
        }
    }
}

// Test function for enemy clas..
void Game::testEnemy() {


    Enemy test(1, 100, EnemyType::Ground, 10, path_.getWaypoints());
    test.setPosition(100, 100);
    test.setTexture(enemy_textures_.get(Textures::Enemy1));

    enemies_.push_back(std::make_shared<Enemy>(test));

    Enemy test2(30, 60, EnemyType::Split, 10, path_.getWaypoints());
    test2.setPosition(100, 50);
    test2.setTexture(enemy_textures_.get(Textures::Enemy1));
    enemies_.push_back(std::make_shared<Enemy>(test2));

    Enemy test3(900, 30, EnemyType::Ground, 10, path_.getWaypoints());
    test3.setPosition(100, 70);
    test3.setTexture(enemy_textures_.get(Textures::Enemy1));
    enemies_.push_back(std::make_shared<Enemy>(test3));

    //Projectile* missl = new MissileProjectile(sf::Vector2f(300,100), 50, enemies_.front());
    ////this actually renders
    //missl->setTexture(tower_textures_.get(Textures::Tower2));

    //projectiles_.push_back(missl);
}

//This function is used to test a splitting enemy functionality, i used the
//tower texture to make it easier to debug, the idea is that a type of enemy, at this
//point i just used Flying as the tag, upon death will split into two smaller enemies
//currently this works but the path doesnt seem to work properly yet
void Game::testEnemySplit(sf::Vector2f position, std::queue<sf::Vector2f> waypoints) {
    Enemy split(30, 60, EnemyType::Ground, 10, waypoints);
    split.setPosition(position);
    split.setTexture(enemy_textures_.get(Textures::Enemy1));

    enemies_.push_back(std::make_shared<Enemy>(split));
}

void Game::updateMenus() {
    // If a tower is being dragged, update it's position
    if (dragged_) {
        shop_->drag(this);
    }

    // Updates displayed wallet amount and health
    shop_->update(player_);

    // If the alternative menu has been closed delete it
    if (menuInactive) {
        alternativeMenu_ = nullptr;
        menuInactive = false;
    }
}

void Game::loadTextures(){

    //Load the Map texture
    if (!map.texture.loadFromFile("grass.jpeg"))
    {
        return;
    }
    
    map.background.setTexture(map.texture);
    // Towers  
    tower_textures_ = ResourceContainer<Textures::TowerID, sf::Texture>();

    tower_textures_.load(Textures::BulletTower, "tower1.png");
    tower_textures_.load(Textures::BombTower, "tower2.png");
    tower_textures_.load(Textures::MissileTower, "tower3.png");//pause button texture needs to be changed to its own texture class later
    tower_textures_.load(Textures::FreezingTower, "tower4.png");
    tower_textures_.load(Textures::PoisonTower, "tower5.png");
    
    // Enemies
    enemy_textures_ = ResourceContainer<Textures::EnemyID, sf::Texture>();

    enemy_textures_.load(Textures::Enemy1, "enemy.png");
    enemy_textures_.load(Textures::Enemy2, "enemy_flying.png");
    enemy_textures_.load(Textures::Enemy3, "enemy_weapon.png");

    // Projectiles
    projectile_textures_ = ResourceContainer<Textures::ProjectileID, sf::Texture>();

    projectile_textures_.load(Textures::Bullet, "bullet.png");
    projectile_textures_.load(Textures::Bomb, "bomb.png");
    projectile_textures_.load(Textures::Missile, "missile.png");
    
    // Others
    various_textures_.load(Textures::Pause, "pausebutton.png");
    various_textures_.load(Textures::Castle, "thinCastle.png");
    various_textures_.load(Textures::Dirt, "dirt.png");
    various_textures_.load(Textures::Upgrade, "Upgrade.png");
    various_textures_.load(Textures::Sell, "Money.png");
    various_textures_.load(Textures::Continue, "okay.png");
    // Load font
    font_.loadFromFile("OpenSans_Condensed-Bold.ttf");
}