#include "levelManager.hpp"
#include "game.hpp"

int LevelManager::getCurrentLevel() const{
    return currLevel_;
}

int LevelManager::getLevelTotal() const{
    return levelTotal_;
}

bool LevelManager::readingSuccessfull(){
    return readingSuccess_;
}

void LevelManager::readLevels(){
    std::ifstream file(src_);

    if(file.rdstate() & (file.failbit | file.badbit)){ //failure
        readingSuccess_ = false;
        return;
    } 

    std::string line;

    std::getline(file,line); //disregards first line which is the example

    while (std::getline(file,line))
    {
        int enemyNum, waveNum, enemyType;
        float waitTime;
        std::vector<int> enemyTypes;
        char comma;

        std::istringstream iss(line);

        iss >> enemyNum >> comma >> waveNum >> comma >> waitTime;

        if (iss.fail() || iss.bad()){ //failure
            readingSuccess_ = false;
            return;
        }

        while (iss >> comma >> enemyType)
        {
            enemyTypes.push_back(enemyType);
        }
        
        if (iss.fail() && !iss.eof()){ //failure
            readingSuccess_ = false;
            return;
        }

        std::map<std::string, variantData> entry;
        entry["enemyAmount"] = enemyNum;
        entry["waves"] = waveNum;
        entry["waitTime"] = waitTime;
        entry["enemyTypes"] = enemyTypes;

        levelSpecs_.push_back(entry);
        readingSuccess_ = true;
    }
}


void LevelManager::update(){
    //this needs to come from game
    float dt = game_.getTime().asSeconds();

    waitTime_ -= dt;

    if(waitTime_ > 0) {
        return;} //time left, return early

    //if there are waves left for the level

    if(std::get<int>(levelSpecs_[currLevel_]["waves"]) > 0) {
        
        initiateEnemies(); 
    }
    else { 
        // Check if all enemies are dead before advancing level
        if (game_.enemies_.empty()) {
            if (!game_.projectiles_.empty()) {
                for (auto& i : game_.projectiles_) {
                    delete i;
                }
                game_.projectiles_.clear();
            }
            game_.projectiles_.clear();
            currLevel_ ++; //move to next level
            player_.addMoney(50*currLevel_);
            player_.levelUp();

            // Create menu between levels
            if(currLevel_ < levelTotal_){
                // If an upgrade menu was open reset the active tower
                if (game_.alternativeMenu_) {
                    game_.activeTower_ = nullptr;
                }
                
                game_.alternativeMenu_ = std::make_unique<Menu>();
                game_.alternativeMenu_->createMenu(MenuType::Level, &game_);
                game_.paused_ = true;
            }
            
            
        }
    }

}

void LevelManager::initiateEnemies(){
    //gets the vector of different types
    auto entry = levelSpecs_[currLevel_].find("enemyTypes");
    const std::vector<int>& enemyTypes = std::get<std::vector<int>>(entry->second);

    //provided more variance than rand()
    std::random_device rd;
    std::uniform_int_distribution<int> range (0, enemyTypes.size()-1);

    //generating enemies
    for(int i = 0; i < std::get<int>(levelSpecs_[currLevel_]["enemyAmount"]); i++){
        //randomly chooses which type from the allowed ones
        int enemyTypeIndex = range(rd);

        //creates said enemy --> pushes it to list of enemies
        switch (enemyTypes[enemyTypeIndex])
        {
        case 0:
        {
            Enemy enemy(30, 60, EnemyType::Ground, 10, path_.getWaypoints());
            enemy.setTexture(game_.enemy_textures_.get(Textures::Enemy1));
            game_.enemies_.push_back(std::make_shared<Enemy>(enemy));
            break;
        }
        case 1:
        {
            Enemy enemy(30, 80, EnemyType::Flying, 10, path_.getWaypoints());
            enemy.setTexture(game_.enemy_textures_.get(Textures::Enemy2));
            game_.enemies_.push_back(std::make_shared<Enemy>(enemy));
            break;
        }
        case 2:
        {
            Enemy enemy(30, 80, EnemyType::Split, 10, path_.getWaypoints());
            enemy.setPosition(100, 0);
            enemy.setTexture(game_.enemy_textures_.get(Textures::Enemy3));
            game_.enemies_.push_back(std::make_shared<Enemy>(enemy));
            break;
        }

        default:
            std::cout << "failed to initialise enemy" << std::endl;
            break;
        }
    }

    //resets the wait time
    waitTime_ = std::get<float>(levelSpecs_[currLevel_]["waitTime"]);

    //removes a wave
    std::get<int>(levelSpecs_[currLevel_]["waves"])--;
}