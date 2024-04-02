#include <SDL.h>
#include <stdio.h>
#include "Controller.h"
#include "Pathfinding.h"
//#include "Game.h"


int Controller::mouseX = 0;
int Controller::mouseY = 0;


//Keeps track if game is running
bool Controller::quit = false;
//Event handler
SDL_Event e;



void Controller::controller()
{
	//Set mouse pos
	SDL_GetMouseState(&Controller::mouseX, &Controller::mouseY);
	//printf("Mouse X: %i Mouse Y: %i\n", Controller::mouseX, Controller::mouseY);
	//Declare classes
	Pathfinding pathfinding;
	//Handle events on queue
	if (SDL_PollEvent(&e) != 0)
	{
		//printf("input detected: %i\n", e.type);
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			Controller::quit = true;
		}

		int buttonCode = 0;

		//MOUSE
		Uint32 mouseState = SDL_GetMouseState(NULL, NULL);
		//User clicks
		//printf("mouse input: %i \n", mouseState);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

			//printf("mouse input: %i \n", mouseState);
			//LEFT CLICK
			if (mouseState == 1)
			{
				//printf("Mouse X: %i Mouse Y: %i\n", Controller::mouseX, Controller::mouseY);
				buttonCode = 1;

			}

			//RIGHT CLICK
			if (mouseState == 4)
			{
				buttonCode = 2;

			}

			//MIDDLE CLICK
			if (mouseState == 2)
			{
				buttonCode = 4;

			}
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			//LEFT CLICK
			if (mouseState == 1)
			{
				//printf("Dragged left click\n");
				buttonCode = 11;

			}

			//RIGHT CLICK
			if (mouseState == 4)
			{
				//printf("Dragged right click\n");
				buttonCode = 12;

			}

			//MIDDLE CLICK
			if (mouseState == 2)
			{
				//printf("Dragged middle click\n");
				buttonCode = 14;


			}
		}


		//Keyboard
		if (e.type == 768)
		{
			buttonCode = 3;

		}

		// send button code to all places
		pathfinding.control(buttonCode);

	}
}