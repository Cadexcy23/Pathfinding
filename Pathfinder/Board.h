#pragma once
#ifndef vector
#include <vector>
#endif
#ifndef Artist
#include "Artist.h"
#endif
class Board {
public:
	struct node {
		Artist::RGBA RGBA;
		bool walkable;
	};

	static Artist::point startPoint;
	static Artist::point goalPoint;
	static Artist::point playerPoint;
	static int mapSize;

	static std::vector<std::vector<Board::node>> mapNodes;
	static std::vector<std::vector<bool>> reachableNodes;
	void initBoard();
	//std::vector<std::vector<bool>> findPath();
	void draw();
	void update();
};