#ifndef MENU
#define MENU
#include <SFML/Graphics.hpp>
#include <list>
#include "button.hpp"
#include "game.hpp"
#include "tower.hpp"

// These are used in createMenu()
// the enum determines what type of menu is created:
// Which buttons are added etc.
enum class MenuType{
    Shop,
    Upgrade,
    Begin,
    Level
};
/**
 * @brief Class for storing a collection of buttons, a menu.
 *
*/
class Menu {
public:
    /**
     * @brief Draws all the objects in the menu.
     * 
     * @param window window onto which the objects get drawn
    */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Checks if a button in the menu has been pressed.
     * 
     * Checks if the mouse has clicked a button. If a button has been clicked
     * calls getAction() on the button and does the corresponding action
     * 
     * @param game Pointer to the game object
    */
    void checkButtons(Game* game);

    /**
     * @brief Creates the buttons and texts of a menu
     * 
     * @param menu Enumerator which tells the type of menu being created
     * @param game Poiner to the game object
    */
    void createMenu(MenuType menu, Game* game);

    /**
     * @brief Updates the status of the menu.
     * 
     * Updates the texts containing the money the player has and the health
     * 
     * @param player Reference to the player object
    */
    void update(Player& player);

    /**
     * @brief Implements drag&drop placing of towers
     * 
     * If the mouse button is still pressed, moves the tower so it follows the mouse
     * if the button is no longer pressed, checks if the player has enough money for 
     * the tower and if it can be placed, and if the conditions are met adds the tower to 
     * the game object
     * 
     * @param game pointer to the game object
     * @see canBePlaced()
    */
    void drag(Game* game);

    /**
     * @brief Draws active tower range.
     * 
     * @param game pointer to the game object
    */
    void drawRange(Game* game);
private:

    /**
     * @brief Adds a new tower to the game, called in checkButtons.
     * 
     * @param tower Pointer to new tower being built
     * @param game Pointer to game 
    */
    void newTower(std::shared_ptr<Tower> tower, Game* game);

    /**
     * @brief Checks if a tower can be placed in its current location.
     * 
     * @param game Pointer to the game object
     * @return true, if the tower can be placed
    */
    bool canBePlaced(Game* game);

    std::list<Button> buttons_;
    std::vector<sf::Text> texts_;
    sf::RectangleShape bg_;
};

#endif