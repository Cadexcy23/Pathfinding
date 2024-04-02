#include <vector>
#include <time.h>
#include "Board.h"
#include "Artist.h"
#include "Pathfinding.h"

std::vector<std::vector<Board::node>> Board::mapNodes;

std::vector<std::vector<bool>> Board::reachableNodes;

Artist::point Board::startPoint = { 1, 1 };
Artist::point Board::goalPoint = { 9, 9 };
Artist::point Board::playerPoint = { 1, 1 };
int Board::mapSize = 36;
double playerLastMoveTime = time(NULL);
int playerMoveSpeed = 1000;
//controlles how big the squares are
int scale = 720 / Board::mapSize;

void resizeBoard(int size)
{
	Board::mapNodes.resize(size);
	for (int i = 0; i < size; i++)
		Board::mapNodes[i].resize(size);

	
}

void randGenBoard()
{
	int size = Board::mapSize;
	
	srand(clock());
	for (int y = 0; y < Board::mapNodes.size(); y++)
	{
		for (int x = 0; x < Board::mapNodes.size(); x++)
		{
			//place random walls 1/4
			int randNum = rand() % 4;
			if (randNum == 0)
			{
				Board::mapNodes[x][y].RGBA.r = 100;
				Board::mapNodes[x][y].RGBA.g = 100;
				Board::mapNodes[x][y].RGBA.b = 100;
				Board::mapNodes[x][y].RGBA.a - 255;
				Board::mapNodes[x][y].walkable = false;
			}
			else
			{
				Board::mapNodes[x][y].RGBA.r = 255;
				Board::mapNodes[x][y].RGBA.g = 255;
				Board::mapNodes[x][y].RGBA.b = 255;
				Board::mapNodes[x][y].RGBA.a - 255;
				Board::mapNodes[x][y].walkable = true;
			}
		}
	}
			
	//block off edges
	//left
	for (int y = 0; y < Board::mapNodes.size(); y++)
	{
		Board::mapNodes[0][y].RGBA.r = 100;
		Board::mapNodes[0][y].RGBA.g = 100;
		Board::mapNodes[0][y].RGBA.b = 100;
		Board::mapNodes[0][y].RGBA.a - 255;
		Board::mapNodes[0][y].walkable = false;
	}
	//right
	for (int y = 0; y < Board::mapNodes.size(); y++)
	{
		int rightMost = Board::mapNodes.size() - 1;
		Board::mapNodes[rightMost][y].RGBA.r = 100;
		Board::mapNodes[rightMost][y].RGBA.g = 100;
		Board::mapNodes[rightMost][y].RGBA.b = 100;
		Board::mapNodes[rightMost][y].RGBA.a - 255;
		Board::mapNodes[rightMost][y].walkable = false;
	}
	//top
	for (int x = 0; x < Board::mapNodes.size(); x++)
	{
		Board::mapNodes[x][0].RGBA.r = 100;
		Board::mapNodes[x][0].RGBA.g = 100;
		Board::mapNodes[x][0].RGBA.b = 100;
		Board::mapNodes[x][0].RGBA.a - 255;
		Board::mapNodes[x][0].walkable = false;
	}
	//bottem
	for (int x = 0; x < Board::mapNodes.size(); x++)
	{
		int bottemMost = Board::mapNodes.size() - 1;
		Board::mapNodes[x][bottemMost].RGBA.r = 100;
		Board::mapNodes[x][bottemMost].RGBA.g = 100;
		Board::mapNodes[x][bottemMost].RGBA.b = 100;
		Board::mapNodes[x][bottemMost].RGBA.a - 255;
		Board::mapNodes[x][bottemMost].walkable = false;
	}
			
			
		
	
	//set goal point to bottem right
	Board::goalPoint.x = Board::mapNodes.size() - 2;
	Board::goalPoint.y = Board::mapNodes.size() - 2;
	//Board::goalPoint.x = rand() % (Board::mapNodes.size() - 2) + 1;
	//Board::goalPoint.y = rand() % (Board::mapNodes.size() - 2) + 1;
	//color start point and goal
	//start
	Board::mapNodes[Board::startPoint.x][Board::startPoint.y].RGBA.r = 0;
	Board::mapNodes[Board::startPoint.x][Board::startPoint.y].RGBA.g = 255;
	Board::mapNodes[Board::startPoint.x][Board::startPoint.y].RGBA.b = 0;
	Board::mapNodes[Board::startPoint.x][Board::startPoint.y].RGBA.a - 255;
	Board::mapNodes[Board::startPoint.x][Board::startPoint.y].walkable = true;
	//goal			
	Board::mapNodes[Board::goalPoint.x][Board::goalPoint.y].RGBA.r = 255;
	Board::mapNodes[Board::goalPoint.x][Board::goalPoint.y].RGBA.g = 0;
	Board::mapNodes[Board::goalPoint.x][Board::goalPoint.y].RGBA.b = 255;
	Board::mapNodes[Board::goalPoint.x][Board::goalPoint.y].RGBA.a - 255;
	Board::mapNodes[Board::goalPoint.x][Board::goalPoint.y].walkable = true;
}

void Board::initBoard()
{
	resizeBoard(Board::mapSize);
	randGenBoard();

	Board::reachableNodes.resize(Board::mapSize);
	for (int i = 0; i < Board::mapSize; i++)
		Board::reachableNodes[i].resize(Board::mapSize);
}

void drawPath()
{
	Artist artist;

	artist.changeRenderedColor(255, 255, 0, 100);

	for (int i = 0; i < Pathfinding::path.size(); i++)
	{
		artist.drawRectangle(Pathfinding::path[i].x * scale, Pathfinding::path[i].y * scale, scale, scale);
	}
}

void drawBoard()
{
	Artist artist;
	for (int x = 0; x < Board::mapNodes.size(); x++)
	{
		for (int y = 0; y < Board::mapNodes.size(); y++)
		{
			artist.changeRenderedColor(Board::mapNodes[x][y].RGBA.r, Board::mapNodes[x][y].RGBA.g, Board::mapNodes[x][y].RGBA.b);
			artist.drawRectangle(x * scale, y * scale, scale, scale);
		}
	}

	for (int x = 0; x < Board::reachableNodes.size(); x++)
	{
		for (int y = 0; y < Board::reachableNodes.size(); y++)
		{
			artist.changeRenderedColor(0, 100, 50, 100);
			if (Board::reachableNodes[x][y])
			{
				artist.drawRectangle(x * scale, y * scale, scale, scale);
			}
		}
	}

	if (Board::reachableNodes[Board::goalPoint.x][Board::goalPoint.y])
	{
		drawPath();
		printf("Steps Taken: %i \n", Pathfinding::path.size());

		artist.changeRenderedColor(0, 255, 0);
	}
	else if (!Pathfinding::frontier.empty())
	{
		artist.changeRenderedColor(255, 255, 0);
	}
	else
	{
		artist.changeRenderedColor(255, 0, 0);
	}
	artist.drawRectangle(Artist::SCREEN_WIDTH - 20, 0, 20, 20);

	artist.changeRenderedColor(0, 0, 255);
	artist.drawRectangle(Board::playerPoint.x * scale + scale / 6, Board::playerPoint.y * scale + scale / 6, scale / 1.5, scale / 1.5);
}

void Board::draw()
{
	drawBoard();
}

void Board::update()
{
	if (playerLastMoveTime < time(NULL))
	{
		playerLastMoveTime = time(NULL);
		if (Board::reachableNodes[Board::goalPoint.x][Board::goalPoint.y])
		{
			int currentPlayerPathIndex = 0;
			for (int i = 0; i < Pathfinding::path.size(); i++)
			{
				if (Pathfinding::path[i].x == playerPoint.x && Pathfinding::path[i].y == playerPoint.y)
				{
					currentPlayerPathIndex = i;
				}
			}
			if (currentPlayerPathIndex - 1 < 0)
			{
				playerPoint = Board::goalPoint;
			}
			else
			{
				playerPoint = Pathfinding::path[currentPlayerPathIndex - 1];
			}
		}
	}
}