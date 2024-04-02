#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include "Artist.h"
#include "Controller.h"
#include "Board.h"
#include "Pathfinding.h"



int main(int argc, char* argv[])
{
	//Declare Artist and controller
	Artist artist;
	Controller controller;
	Board board;
	Pathfinding pathfinding;
	

	//Start up SDL and create window
	if (!artist.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!artist.loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//loading setting ect
			
			board.initBoard();

			pathfinding.initPathfinder();
			
			//board.findPath();
			
			//While application is running
			while (!Controller::quit)
			{
				//Clear screen
				artist.clearScreen();




				//Updates game world
				pathfinding.update();
				board.update();

				//Draw everything
				artist.draw();

				//Checks for user input
				controller.controller();




				//Update screen
				artist.updateScreen();
			}
		}
	}

	//Free resources and close SDL
	artist.close();

	return 0;
}