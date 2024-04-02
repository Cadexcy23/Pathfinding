# Pathfinding
Description: Program for testing pathfinding algorithms.\
Author: Caden Metzgus\
Created: 2/7/2019\
Platform: Windows

## Controls
Up Arrow - Toggle pathing.\
Right Arrow - Take 1 step.

## Execution
A randomized board of tiles is created. Upon activation, the program will attempt to find a path from the start(green) to the goal(magenta).\
The blue square represents a character looking for the path, upon success it will draw a yellow path and follow it.\
![Pathfinder](https://github.com/Cadexcy23/Pathfinding/assets/51723869/4787d4c3-fefd-4326-b8e3-702e39383824)\
Board size, start, and goal are all adjustable in [Board.cpp](https://github.com/Cadexcy23/Pathfinding/blob/master/Pathfinder/Board.cpp).
```C++
Artist::point Board::startPoint = { 1, 1 };
Artist::point Board::goalPoint = { 34, 34 };
Artist::point Board::playerPoint = { 1, 1 };
int Board::mapSize = 36;
```
There are 3 modes for diagonals, disabled, enabled, and restricted.
 * Disabled - can only move up down left and right.
 * Enabled - allowed to move diagonally.
 * Restricted - allowed to move diagonally, but only if the combined directions are open.

This can be found in the file [Pathfinding.cpp](https://github.com/Cadexcy23/Pathfinding/blob/master/Pathfinder/Pathfinding.cpp).
```C++
//0 disabled
//1 enabled
//2 restricted
int diagToggle = 2;
```

The Square in the top right reflects the current state of the pathfinder.
 * Yellow - still looking
 * Green - path found
 * Red - no path possible
