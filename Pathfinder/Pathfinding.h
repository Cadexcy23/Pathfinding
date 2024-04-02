#pragma once
#ifndef vector
#include <vector>
#endif
#ifndef Artist
#include "Artist.h"
#endif
class Pathfinding {
public:
	static std::vector<Artist::point> frontier;
	static std::vector<Artist::point> path;

	void initPathfinder();

	void updatePathfinder();

	void control(int input);

	void update();

	//std::vector<std::vector<bool>> findPath(int h, int w, Artist::point start, Artist::point goal, std::vector<std::vector<int>>* paths);

};