# Meeting Notes
In this file, you are required to take notes for your weekly meetings. 
In each meeting, you are required to discuss:

1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any


# Meeting 27.11.2023 14::00

**Participants**: 
1. Leo
2. Otto
3. Tuan
4. Pavel
5. Ellen
6. Tran Duong (advaisor)

## Summary of works
1. Leo

    Created path class that holds waypoints to direct enemy movement
    Improved enemys movement functions to make use of waypoints

2. Otto

   Was able to get parts of the project to compile and be renderd to screen:
   - Towers can be created via drag and drop
   - Towers can only be created if player has enough money
   - Game pause button

3. Ellen

    Created two derived classes for projectile: Bullet and Bomb
    Slight changes to projectile methdos to better work with derived classes and towers

4. Pavel

    Created two derived classes for Tower: Bullet and Bomb
    Moved and improved tower update logic into it's own function to have it better work with derived classes


5. Tuan

    Continued working on map class to create a path, implementing it in a grid like way

## Challenges

1. How to move enemies along path created by map
2. Connecting classes togheter in a functioning way

## Actions
1. Tuan is going to work on being able to visualise / render map class to create a path for enemies to move on
2. Leo is going to continue working on enemy movement along the path, and consider using the maps grid for direction.
3. Ellen is going continue to coordinate with Pavel on what kind of projectiles are needed and work on player buying / updating towers
4. Pavel will continue implementing derived tower classes and improving on the main game logic
5. Otto will continue working on rendering game objects and the players interactions with them (moving, adding, different buttons)

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
Main classes are getting there and some derived classes already exist. Parts of project compile and render. Classes still need to be combined for a functioning entirety.

### TODOs
1. Everyone will aim to have their main classes fully implemented by the end of the week to be able to start rendering and testing the project as a whole.