# Orcs n Towers

## Overview

Orcs n Towers is a tower defense game set in a fantasy setting, where orcs and other such monsters try to reach and destroy the player's castle, the player must defend against the monsters by placing different towers with specific roles. The player will have a set number of hitpoints that are depleted when enemies reach the castle. When all hitpoints are lost the player loses.

The monsters traverse a path, along which the player can place their towers. There is three different paths of which one is chosen at random for the duration of the game. Once a monster is inside a towers range, depending on the towers it will either create a projectile that matches the towers type, or apply a slowing or poison effect on the monster. Certain towers can only affect certain monsters.

The player can buy as many Towers as they can afford throughout the game, as well as upgrade them to increase the damage the tower will cause the monster and sell them. The player earns money by killing enemies as well as by progressing through the levels.

The game has 5 different levels of increasing difficulty, by introducing more monsters in amount and type at quicker intervals. The game is won once the player has defeated all levels. The player loses HP every time a monster reaches the castle, and once the HP is zero, the game is lost.

## Instructions

Once you have started the game, to place towers on map, drag and drop them from the side bar to an appropriate place. Note that towers cannot be built on the path. To cancel the purchase of a tower drag it back onto the side bar. The towers range can be seen while dragging it as well as by clicking on it once on map. To upgrade or sell a tower, click on the tower and choose the wanted action from the menu that appeared on the bottom of the screen, there you can also see the towers specifications. 

A level is completed once all enemies from that level have been killed. To move on to the next level, press the "next level" button that appears on the screen. The game can be paused by pressing the "pause" button on the side bar, there the player can also see their current level and how much money and HP they have.

Custom levels and paths can be created in levels.csv and paths.csv respectively, found in assets folder, read formatting instructions carefully.

## How to compile the program

To compile the game, as taken from git, on the command line:

    1. create an empty directory where the build files will be written
    2. change directory to that directory
    3. run: cmake ..
    4. run: make
    5. run: ./TD

SFML multi-media library (minimum version 2.5) is required.

## Testing

Testing was mostly done directly in the source files, in either a project branch or on master branch. The first kinds of tests were simply rendering the game objects to be able to see them on the screen, once that was at least partially working, it was easier to gauge what exactly the game objects were doing and testing how the objects interacted with each other was started. Print statements were used as well to make it easer to follow which part of the code was being executed, and if it was the expected part.

Enemies movement was initially tested by hardcoding waypoints, to see that the logic worked, and enemies travesed the path that they were supposed to. Once towers and enemies were able to be rendered on the screen, their interactions with each other could be tested, namely that towers recognized that enemies we're within their range and could pick one to target.

When towers could clock on to enemies, the creation of projectiles by towers could be tested. Initially there were some minor issues with initializing projectiles due to different ideas on what should be passed to constructor, but that was easily solved with some adjustments. Once projectiles could be created their movement and ability to hit enemies was tested, initially they didn't seem to move; with some adjustments to their values that dictated how far they could move from their tower, it could be determined that projectiles were able to move towards enemies and hit them, and therefore cause damage to them. 

When projectiles could hit enemies, the killing of enemies could be better tested, to see that enemies would actually take damage from projectiles, and once their HP would reach zero, they would die and be deleted, which they did. The testing of enemies causing damage to the player by reaching the castle, and dying when they do so, was done by allowing the enemies to reach the castle.

Not being able to buy towers if player didn't have enough money or, place towers on top of each other or on the path was simply tested by trying to do so. User interactions with the game, like the ability to pause/unpause, displaying tower information, upgrading or selling towers and moving on to the next level were tested by executing the action and observing the outcome. 

Reading both levels and paths from file was tested by reading the content into containers and printing the contents as well as the status of the reading success. Firstly with correctly formatted input to see that the reading logic worked, and then with incorrectly formatted input, to test the error handling. As expected, incorrectly formatted input caused reading success to return false, and thus indicating reading failed. Once it was determined the reading of levels worked, the level execution was tested by playing through the whole game.

Additionally, we had encountered segmentation faults on different stages of development. These were addressed by running the executable with GNU Debugger. 

## Work log

##### Division of work / main responisbilities:


Pavel Filippov:
    - Tower class and it's derived classes (bullet-, bomb-, missile-, poison-, and freezing tower)
    - Game class

Otto Litkey:
    - Graphics (buttons, textures)
    - User interaction
    - Menu class
    - Resource container template class

Ellen Molin:
    - Projectile class and it's derived classes (bullet-, bomb-, and missile projectile)
    - LevelManager class
    - Reading paths from file
    - Player class

Leo Saied-Ahmad:
    - Enemy class
    - Path class

Tuan Vu:
    - Map class
    - Some graphics related to map and path of the game.

##### Weekly breakdown

**Week 1**

Pavel Filippov:
    - Initialised implementation of base tower class.
    - Estimated workload: 10 hours

Otto Litkey: 
    - Initialised implementation of class(es) responsible for graphics.
    - Estimated workload: 6 h

Ellen Molin:
    - Initialised implementation of Player and base Projectile classes.
    - Estimated workload: 5h

Leo Saied-Ahmad:
    - Intialised implementation of base Enemy class.
    - Estimated workload: 

Tuan Vu:
    - Initialised implementation of Map class.
    - Estimated workload: 6h

**Week 2**

Pavel Filippov:
    - Continued implementation of base tower class.
    - Estimated workload: 10 hours

Otto Litkey: 
    - Initialised game class and ResourceContainer template class.
    - Estimated workload: 7 h

Ellen Molin:
    - Continued implementation of Player and base Projectile classes.
    - Estimated workload: 8h

Leo Saied-Ahmad:
    - Continued implementation of base Enemy class.
    - Estimated workload: 

Tuan Vu:
    - Continued implementation of Map class.
    - Estimated workload: 8h

**Week 3**

Pavel Filippov:
    - Implemented update function for game class, as well as for towers.
    - Estimated workload: 10 h 

Otto Litkey: 
    - Tested rendering, beginnings of dragging and dropping functionality for creating towers.
    - Estimated workload: 10 h

Ellen Molin:
    - Improved projectile class and added functionality.
    - Estimated workload: 10h

Leo Saied-Ahmad:
    - Improved enemy class functionality, specifically kill and death functions.
    - Estimated workload: 

Tuan Vu:
    - Finished implementing loading map from file, worked on drawing and being able to sell towers
    - Estimated workload: 10h

**Week 4**

Pavel Filippov:
    - Created derived classes bulletTower and bombTower from tower. Moved tower update logic to it's own function.
    - Estimated workload: 15 h

Otto Litkey: 
    - Continued testing rendering, finished drag and drop functionality for creating towers, and added way to pause game.
    - Estimated workload: 10 h

Ellen Molin:
    - Created derived classes bullet and bomb from projectile. Improved projectile methods to better work with derived classes.
    - Estimated workload: 12h

Leo Saied-Ahmad:
    - Created path class for directing enemy movement, and updated enemy's move function to make use of it.
    - Estimated workload: 

Tuan Vu:
    - Continued working on map class so that it worked well with other classes.
    - Estimated workload: 10h

**Week 5**

Pavel Filippov:
    - Implemented missile tower. Worked on rendering projectiles.
    - Estimated workload: 15 h

Otto Litkey: 
    - Implemented a level system in player class. Created menu class, migrated UI elements to work from here. Worked on rendering projectiles.
    - Estimated workload: 15 h

Ellen Molin:
    - Created a missile projectile that follows enemy. 
    - Estimated workload: 12h

Leo Saied-Ahmad:
    - Worked on enemies that split when hit. Worked on graphics: show players state, end screen when player loses.
    - Estimated workload: 

Tuan Vu:
    - Worked on map class, loading background from file
    - Estimated workload: 10h

**Week 6**

Pavel Filippov:
    - Implemented freezing effect tower and poison effect tower. Refined tower logic.
    - Estimated workload: 15 h 

Otto Litkey: 
    - Implemented explosions class to visualise bombs' explosions. Worked on graphics: created textures, show tower ranges. Improved logic behind user interactions with game objects.
    - Estimated workload: 12 h

Ellen Molin:
    - Implemented a levelManager that handles creating and managing levels, reads from file. Added functionality to load paths from file.
    - Estimated workload: 15h

Leo Saied-Ahmad:
    - Implemented slowing effect on enemies and refined enemy movement. Added health status over enemies.
    - Estimated workload: 

Tuan Vu:
    - Implemented a path class that facilitates the creation of paths, incorporating functionality to prevent towers from being built on the designated path.
    - Estimated workload: 10h
    
    
## Software structure

![](graph.png)
@image latex graph.png 

The above image describes the relations between the main classes in the program.

The main function creates an instance of Game, which handles running the game logic and rendering. It creates and stores a sf::RenderWindow object, which handles user input and displaying graphics. The Game class stores lists of Tower, Projectile and Enemy objects. All of these inherit from sf::Sprite, which enables easy drawing and moving. Towers are added by the Menu class, which stores multiple Button objects the user can interact with. The Tower objects create Projectile objects, which the game stores and updates. A Projectile can damage an Enemy object. These are initially added to the list storing Enemy objects by the LevelManager class. The classes Path and Map handle creating the background and the path along which enemies follow. ResourceContainer is used for loading and storing sf::Texture objects.

    
