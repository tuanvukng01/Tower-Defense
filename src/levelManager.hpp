#ifndef LEVELMANAGER
#define LEVELMANAGER

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <fstream>
#include <sstream>
#include <random>

#include "enemy.hpp"
#include "path.hpp"

class Game;

/**
 * @brief Handles the creation and managing of levels
*/
class LevelManager {

    public:
    /**
     * @brief To allow the map holding level information to use different types
    */
    using variantData = std::variant<int, float, std::vector<int>>;

    /**
     * Initialises a levelManager and reads the level information from file.
     * Intitial current level is zero (= level one) to follow indexing convention of level specifications container,
     * to allow easier accessing
     * @param src is the source of the level information file that is to be read
     * @param path is a reference to the path instance that creates the path of the game
     * @param game is a reference to the running game instance
     * @param player is a reference to the player instance of the game
     * @see readLevels()
    */
    LevelManager(const std::string& src, path& path, Game& game, Player& player) : src_(src), path_(path), game_(game), player_(player) {
        readLevels();

        currLevel_ = 0;
        waitTime_ = 0;
        levelTotal_ = levelSpecs_.size();
    }
    ~LevelManager(){}

    /**
     * @returns the current level
    */
    int getCurrentLevel() const;
    
    /**
     * @returns the total number of levels definend
    */
    int getLevelTotal() const;

    /**
     * Updates the level manager, called while game is running.
     * Counts down the wait time between waves of enemies.
     * Initiates more enemies once wait time becomes zero, if there are waves left for the level.
     * Moves to a new level once previous is complete and there are no enemies left.
     * @see initiateEnemies()
    */
    void update();

    /**
     * returns status flag for reading level info from file.
     * @returns True if reading was successfull,
     * false if not
    */
    bool readingSuccessfull();

    private:

    /**
     * Reads from the source file provided in constructor.
     * Disregards first line of file as it is the formatting example.
     * Then reads one line at a time: \n 
     *  - number of enemies per wave, number of waves, wait time between waves into variables \n 
     *  - allowed enemy types into a vector \n
     * Adds the collected values into a map which gets pushed into the vector container that holds all levels.
    */
    void readLevels();

    /**
     * @brief Initiates the amount of enemies that is allowed for the level.
     * Randomly chooses which type of enemy to initiate based on the allowed types for the level.
     * Uses a switch case to initiate the right kind of enemy and adds it to the container of enemies. 
     * Resets the wait time and decreases waves.
    */
    void initiateEnemies();
    
    
    /**
     * @brief Container to hold all the levels.
     * One entry in the outer container (vector) is one level, meaning index 0 is level one.
     * The inner map holds all information regarding the specific level. \n 
     * Keys: "enemyAmount" : the number of enemies allowed per wave (int), "waves" : the number of waves of enemeis allowed per level (int), "waitTime" : the time (in seconds) between waves (float), "enemyTypes" : a vector containing the types of enemies allowed for the level
     * @see Enemy class' type enum EnemyType
     * @see variantData
    */
    std::vector<std::map<std::string, variantData>> levelSpecs_; //!< The container that stores all levels information

    int currLevel_;
    const std::string& src_;
    bool readingSuccess_;
    int levelTotal_;
    float waitTime_;

    path& path_;
    Game& game_;
    Player& player_;
};

#endif