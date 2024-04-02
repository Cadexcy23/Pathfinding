#include <vector>
#include "Pathfinding.h"
#include "Board.h"
#include "Artist.h"

//makes pathfinder autorun
bool toggleOn = false;
//diagnal
int diagToggle = 2;
//keeps trak of current frontier
Artist::point current;

//holds a queue of places to check
std::vector<Artist::point> Pathfinding::frontier;


//keep track of where we have gone
//std::vector<std::vector<bool>> visited;

//keep track of where we came from
std::vector<std::vector<Artist::point>> cameFrom;


//keeptrack of where we can go
std::vector<std::vector<bool>> visitable;


//keeps track of if we found goal
bool foundGoal = false;

//holds the path from goal to start
std::vector<Artist::point> Pathfinding::path;


void Pathfinding::initPathfinder()
{
	int size = Board::mapSize;
	Artist::point start = Board::startPoint;
	frontier.push_back(start);

	cameFrom.resize(size);
	for (int i = 0; i < size; i++)
		cameFrom[i].resize(size);
	Artist::point invalidPoint = { -1, -1 };
	for (int y = 0; y < cameFrom.size(); y++)
	{
		for (int x = 0; x < cameFrom.size(); x++)
		{
			cameFrom[x][y] = invalidPoint;
		}
	}
	Artist::point initStart = { start.x, start.y };
	cameFrom[start.x][start.y] = initStart;

	visitable.resize(size);
	for (int i = 0; i < size; i++)
		visitable[i].resize(size);
	visitable[start.x][start.y] = true;

	Board::reachableNodes = visitable;

	/*int size = Board::mapSize;
	Artist::point start = Board::startPoint;
	frontier.push_back(start);
	
	visited.resize(size);
	for (int i = 0; i < size; i++)
		visited[i].resize(size);
	visited[start.x][start.y] = true;
	
	visitable.resize(size);
	for (int i = 0; i < size; i++)
		visitable[i].resize(size);
	visitable[start.x][start.y] = true;

	Board::reachableNodes = visitable;*/
}

std::vector<Artist::point> getNeighbors(Artist::point start, int diag)
{
	std::vector<Artist::point> returnNeighbors;

	//if (diag)
	//{
	//	returnNeighbors.resize(8);
	//}
	//else
	//{
	//	returnNeighbors.resize(4);
	//}
	

	//up
	returnNeighbors.push_back({ start.x, start.y - 1 });
	//returnNeighbors[0].x = start.x;
	//returnNeighbors[0].y = start.y - 1;
	//right
	returnNeighbors.push_back({ start.x + 1, start.y });
	//returnNeighbors[1].x = start.x + 1;
	//returnNeighbors[1].y = start.y;
	//down
	returnNeighbors.push_back({ start.x, start.y + 1 });
	//returnNeighbors[2].x = start.x;
	//returnNeighbors[2].y = start.y + 1;
	////left
	returnNeighbors.push_back({ start.x - 1, start.y });
	//returnNeighbors[3].x = start.x - 1;
	//returnNeighbors[3].y = start.y;

	if (diag == 1)
	{
		//up right
		returnNeighbors.push_back({ start.x + 1, start.y - 1 });
		//returnNeighbors[4].x = start.x + 1;
		//returnNeighbors[4].y = start.y - 1;
		//down right
		returnNeighbors.push_back({ start.x + 1, start.y + 1 });
		//returnNeighbors[5].x = start.x + 1;
		//returnNeighbors[5].y = start.y + 1;
		//down left
		returnNeighbors.push_back({ start.x - 1, start.y + 1 });
		//returnNeighbors[6].x = start.x - 1;
		//returnNeighbors[6].y = start.y + 1;
		//up left
		returnNeighbors.push_back({ start.x - 1, start.y - 1 });
		//returnNeighbors[7].x = start.x - 1;
		//returnNeighbors[7].y = start.y - 1;
	}
	else if (diag == 2)
	{
		//up right
		if (Board::mapNodes[returnNeighbors[0].x][returnNeighbors[0].y].walkable && Board::mapNodes[returnNeighbors[1].x][returnNeighbors[1].y].walkable)
		{
			returnNeighbors.push_back({ start.x + 1, start.y - 1 });
		}
		//down right
		if (Board::mapNodes[returnNeighbors[2].x][returnNeighbors[2].y].walkable && Board::mapNodes[returnNeighbors[1].x][returnNeighbors[1].y].walkable)
		{
			returnNeighbors.push_back({ start.x + 1, start.y + 1 });
		}
		//down left
		if (Board::mapNodes[returnNeighbors[2].x][returnNeighbors[2].y].walkable && Board::mapNodes[returnNeighbors[3].x][returnNeighbors[3].y].walkable)
		{
			returnNeighbors.push_back({ start.x - 1, start.y + 1 });
		}
		//up left
		if (Board::mapNodes[returnNeighbors[0].x][returnNeighbors[0].y].walkable && Board::mapNodes[returnNeighbors[3].x][returnNeighbors[3].y].walkable)
		{
			returnNeighbors.push_back({ start.x - 1, start.y - 1 });
		}
	}

	return returnNeighbors;
}

void Pathfinding::updatePathfinder()
{
	if (foundGoal)
	{
		return;
	}
	if (frontier.empty())
	{
		return;
	}
	current = frontier.front();
	std::vector<Artist::point> neighbors;
	neighbors = getNeighbors(current, diagToggle);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i].x >= 0 && neighbors[i].x < Board::mapSize && neighbors[i].y >= 0 && neighbors[i].y < Board::mapSize)
		{
			if (cameFrom[neighbors[i].x][neighbors[i].y].x == -1 && cameFrom[neighbors[i].x][neighbors[i].y].y == -1)
			{
				if (Board::mapNodes[neighbors[i].x][neighbors[i].y].walkable)
				{
					frontier.push_back(neighbors[i]);
				}
				cameFrom[neighbors[i].x][neighbors[i].y] = current;
				visitable[neighbors[i].x][neighbors[i].y] = Board::mapNodes[neighbors[i].x][neighbors[i].y].walkable;
				if (neighbors[i].x == Board::goalPoint.x && neighbors[i].y == Board::goalPoint.y)
				{
					foundGoal = true;
				}
			}
		}

	}

	frontier.erase(frontier.begin());
	Board::reachableNodes = visitable;

	if (foundGoal)
	{
		//create path after we found the goal
		current = Board::goalPoint;
		while (current.x != Board::startPoint.x || current.y != Board::startPoint.y)
		{
			path.push_back(cameFrom[current.x][current.y]);
			current = cameFrom[current.x][current.y];
		}
		
		
	}

	/*if (foundGoal)
	{
		return;
	}
	if (frontier.empty())









	{
		return;
	}
	current = frontier.front();
	std::vector<Artist::point> neighbors;
	neighbors = getNeighbors(current);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i].x >= 0 && neighbors[i].x < Board::mapSize && neighbors[i].y >= 0 && neighbors[i].y < Board::mapSize)
		{
			if (!visited[neighbors[i].x][neighbors[i].y])
			{
				if (Board::mapNodes[neighbors[i].x][neighbors[i].y].walkable)
				{
					frontier.push_back(neighbors[i]);
				}
				visited[neighbors[i].x][neighbors[i].y] = true;
				visitable[neighbors[i].x][neighbors[i].y] = Board::mapNodes[neighbors[i].x][neighbors[i].y].walkable;
				if (neighbors[i].x == Board::goalPoint.x && neighbors[i].y == Board::goalPoint.y)
				{
					foundGoal = true;
				}
			}
		}

	}

	frontier.erase(frontier.begin());
	Board::reachableNodes = visitable;*/
}

void Pathfinding::control(int input)
{
	Pathfinding pathfinding;
	switch (input)
	{
	case 3:
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		//right arrow
		if (state[SDL_SCANCODE_RIGHT])
		{
			pathfinding.updatePathfinder();
		}
		//up arrow
		if (state[SDL_SCANCODE_UP])
		{
			if (toggleOn)
			{
				toggleOn = false;
			}
			else
			{
				toggleOn = true;
			}
		}
		break;
	}
}

void Pathfinding::update()
{
	if (toggleOn)
	{
		Pathfinding::updatePathfinder();
	}
}