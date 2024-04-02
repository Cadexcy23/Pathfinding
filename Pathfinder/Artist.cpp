#include <SDL.h>
#include <SDL_image.h>
#include "Artist.h"
#include "Board.h"
//#include "Game.h"


int Artist::SCREEN_WIDTH = 960;
int Artist::SCREEN_HEIGHT = 720;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


bool Artist::init()
{

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Who is Bess Chess?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Artist::SCREEN_WIDTH, Artist::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		Artist artist;
		SDL_Surface* icon = IMG_Load("Resource/icon.png");
		SDL_SetWindowIcon(gWindow, icon);
		SDL_FreeSurface(icon);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
				SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer

			}
		}
	}

	return success;
}

void Artist::clearScreen()
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(gRenderer);
}

void Artist::updateScreen()
{
	SDL_RenderPresent(gRenderer);
}

void Artist::close()
{
	//Free loaded image
	//SDL_DestroyTexture(gBackground);
	//gBackground = NULL;






	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Artist::loadMedia()
{
	Artist Artist;
	//Loading success flag
	bool success = true;


	//Load texture

	//letters
	//loadFontTextures(&Artist::largeFont, "large");
	//loadFontTextures(&Artist::smallFont, "small");


	return success;
}

void Artist::drawLineFromPoints(int sX, int sY, int eX, int eY)
{
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0xFF);
	SDL_RenderDrawLine(gRenderer, sX, sY, eX, eY);
}

Artist::point Artist::drawLineFromAngle(int sX, int sY, float angle, int length)
{
	float rise, run;
	float endX, endY;



	rise = length * sin(angle);
	run = length * sin(M_PI - angle - M_PI / 2);

	endX = sX - run;
	endY = sY - rise;

	//float endAngle = atan2(sX - endY, sY - endX);

	//printf("%f ", atan2(sY - endY, sX - endX));
	//printf("%f \n", atan2(sY - endY, sX - endX) * 180 / M_PI);

	SDL_RenderDrawLine(gRenderer, sX, sY, endX, endY);

	Artist::point endPoint;
	endPoint.x = endX;
	endPoint.y = endY;

	return endPoint;
}

void Artist::changeRenderedColor(int r, int g, int b, int alpha)
{
	SDL_SetRenderDrawColor(gRenderer, r, g, b, alpha);
}

void Artist::drawRectangle(int x, int y, int w, int h)
{
	SDL_Rect tempRect;
	tempRect.x = x;
	tempRect.y = y;
	tempRect.w = w;
	tempRect.h = h;
	SDL_RenderFillRect(gRenderer, &tempRect);
	//draw dark lines around
	Uint8 oldR, oldG, oldB, oldA;
	SDL_GetRenderDrawColor(gRenderer, &oldR, &oldG, &oldB, &oldA);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 100);
	SDL_RenderDrawRect(gRenderer, &tempRect);
	SDL_SetRenderDrawColor(gRenderer, oldR, oldG, oldB, oldA);
}





void Artist::draw()
{
	Board board;

	board.draw();


	//TEMP

}