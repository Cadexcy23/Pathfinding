#pragma once
#include <string>
#ifndef SDL
#include <SDL.h>
#endif // !SDL


class Artist {
public:
	static int SCREEN_WIDTH, SCREEN_HEIGHT;

	struct point {
		int x;
		int y;
	};
	struct RGBA {
		int r;
		int g;
		int b;
		int a;
	};

	void draw();
	//Clears the screen
	void clearScreen();

	//Updates the screen
	void updateScreen();

	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	void drawLineFromPoints(int startX, int startY, int endX, int endY);

	Artist::point drawLineFromAngle(int sX, int sY, float angle, int length);

	void changeRenderedColor(int r, int g, int b, int alpha = 255);

	void drawRectangle(int x, int y, int w, int h);

	//Frees media and shuts down SDL
	void close();
};