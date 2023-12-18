
# Meeting 13.11.2023 14::00

**Participants**: 
1. Filippov Pavel
2. Saied Ahmad Leo
3. Molin Ellen
4. Otto Litkey
5. Vu Tuan

## Summary of works
1. Pavel
	Implementing the Tower class, which acts as a template for different types of towers.

2. Leo
	Implementing Enemy class, which is a base class for different types of enemies. 

3. Otto
	Game class which will run the game loop and ResourceContainer class which stores textures etc
	
4. Ellen 
	Projectile class for the projectiles that towers shoot at enemies. This is the class which will deal damage to enemies. SFML sprites have functionality for checking if they intersect, which is useful here. 
	Player class, buying, selling towers, etc.
	
5. Tuan 
	Map class, implements the path along which enemies move

## Challenges

1. Merging the created classes to make testing the crated classes properly
2. Implementing damage to enemies needs to be coordinated with projectile class
3. Drawing things 

## Actions
1. Everyone: Work on classes we have begun working on. Working should be more coordinated as the classes need to function together.
2. Pavel: update, shoot and lockOn methods for tower class, other remaining adjustments for tower class. main.cpp
3. Leo: Movement for enemies. Damage taking and destroying enemies will probably be adjusted, coordinated with Ellen who has created the projectile class.
4. Otto: Game class further function implementations, Drawing stuff, drag and drop
5. Tuan: Working on map class


## Project status 
Base classes created, next step is to merge these. Rendering things needs to be thinked trough. The classes should maybe be implemented as some SFML class derived objects so SFML:s convinience functions can be used. 


### TODOs
1. Get a rudimentary version of the game running asap. Generally we are trying to get to a state where we have a main function and we are able to test drawing objects and other functionality.


