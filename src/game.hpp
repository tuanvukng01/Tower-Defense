#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include "tower.hpp"
#include "path.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "resource_container.hpp"
#include "player.hpp"
#include <memory> //for shared_ptr
#include "bulletTower.hpp"
#include "button.hpp"
#include "map.hpp"
#include "missileProjectile.hpp"
#include "menu.hpp"
#include <vector>
#include "levelManager.hpp"
#include "explosion.hpp"

class Menu;
// Class for running the game logic

/**
 * @class Game
 * @brief This class runs the game logic
*/
class Game {
    
    friend class Tower;
    friend class BulletTower;
    friend class BombTower;
    friend class MissileTower;
    friend class FreezingTower;
    friend class BombProjectile;
    friend class BulletProjectile;
    friend class MissileProjectile;
    friend class PoisonTower;
    friend class Menu; 
    friend class LevelManager;

public:
    Map map;
    Game();

    /**
     * @brief this function is called from the main function to run the game.
     * 
     * If the window remains open, calls processEvents(), update(), and render() in this order.
     * 
     * @see processEvents()
     * @see update()
     * @see render()
    */
    void run();

    ~Game(){
        
        enemies_.clear();

        for(auto i : projectiles_){
            delete i;
        } 
        projectiles_.clear();

        towers_.clear();

        // Menus deleted by unique_ptr
    }

    /**
     * @brief Returns the path, which enemies follow
     * 
     * @return path& the path
    */
    path& getPath();
private:
    /**
     * @brief processes user input
     * 
     * Gets widow events from SFML and checks if the window has been closed, or if the mouse button has been pressed.
     * If the mouse button has been pressed checks if a button has been pressed by using Menu::checkButtons() and checks if a 
     * tower has been clicked to open the upgrade menu.
     * 
     * @see checkTowers()
     * 
    */
    void processEvents();

    /**
     * @brief Updates the state of objects in the game.
     * 
     * First resets the timer, then handles updating objects by using their update functions.
    */
    void update();

    /**
     * @brief Renders all objects onto the window.
     * 
     * Clears window then draws objects.
     * First draws the background and path, then iterates over towers, projectiles, enemies and explosions.
     * Then draws some miscalennous things, like the tower being dragged if it exists and it's range.
     * Menus are drawn last so they do not end up under anything.
    */
    void render();

    /**
     * @brief Helper function called in constructor, loads all textures.
    */
    void loadTextures();

    /**
     * @brief Used for testing the game, creates a hardcoded path.
    */
    void createPath(); //this will create the path that the enemies will traverse (this should also be rendered visually in the game)
    
    /**
     * @brief Check if a tower has been clicked.
     * 
     * If the mouse button has been pressed but no Button object was clicked, this checks if a purchased tower has been clicked.
     * If a tower has been clicked, creates an upgrade menu, for upgrading or selling the tower.
    */
    void checkTowers();


    void testEnemy();
    void testEnemySplit(sf::Vector2f position, std::queue<sf::Vector2f> waypoints);

    /**
     * @brief Helper function for updating the menus in game, called in update().
     * 
     * If a tower is being dragged calls Menu::drag() to update it's position. Then updates the texts on screen. 
     * If an alternative menu has been closed deletes the alternative menu.
    */
    void updateMenus();

    //adding a function to return the elapsed time
    sf::Time getTime() const;
    //I am adding a clock and time functionality that will need to be used for enemy movement and updating and other game logic
    sf::Clock clock_;
    sf::Time time_;
    sf::RenderWindow window_;
    
    std::list<std::shared_ptr<Tower>> towers_;
    std::list<std::shared_ptr<Enemy>> enemies_;
    std::list<Projectile*> projectiles_;
    std::list<Explosion*> explosions_;
    path path_;

    bool dragged_; ///< Indicates if a tower is currently being dragged into place
    bool paused_; ///< Is the game paused
    bool isGameOver_=false; ///< Is the game over because the player has died to an enemy
    bool isGameFinished_ = false; ///< Completed game
    sf::Font font_; ///< Stores text font
    sf::Text gameOverText;
    sf::Text gameFinishedText;
    sf::Sprite castle_sprite_;

    std::unique_ptr<Menu> shop_; ///< Shop on left side
    std::unique_ptr<Menu> alternativeMenu_; ///< stores menu for upgrading, beginning game, and advancing to next level
    std::shared_ptr<Tower> activeTower_; ///< Pointer to tower that is being upgraded or dragged into place
    bool menuInactive = false; ///< Indicates if the alternative menu is closed and needs to be deleted

    ResourceContainer<Textures::TowerID, sf::Texture> tower_textures_;
    ResourceContainer<Textures::EnemyID, sf::Texture> enemy_textures_;
    ResourceContainer<Textures::ProjectileID, sf::Texture> projectile_textures_;
    ResourceContainer<Textures::Various, sf::Texture> various_textures_;

    Player player_; 

    LevelManager levelManager_;
};

#endif