#ifndef ASTAR_H_
#define ASTAR_H_
#include "level.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>

using Coords = std::pair<int, int>;


using namespace std;


struct AstarNode{
	Coords coords;
	int f;
	int g;
	int h;
	AstarNode* parent;
	AstarNode(Coords coords, int f, int g, int h, AstarNode* parent){
		this->coords = coords;
		this->f = f;
		this->g = g;
		this->h = h;
		this->parent = parent;
	}
	AstarNode(Coords coords){
		this->coords = coords;
		this->f = 0;
		this->g = 0;
		this->h = 0;
		this->parent = nullptr;
	}
	vector<Coords> reconstructPath(){
		vector<Coords> path;
		AstarNode* current = this;
		while(current->parent != nullptr){
			path.push_back(current->coords);
			current = current->parent;
		}
		return path;
	}
};

class Astar {
    public:
        static std::vector<std::pair<int, int>> astarDirection(std::pair<int, int> start, std::pair<int, int> finish, Grid grid);
		static std::vector<Coords> calculatePath(Coords start, Coords end, Grid grid);
		static AstarNode* findLowest(std::vector<AstarNode*> open);
		static AstarNode* findInOpen(Coords coords, std::vector<AstarNode*> &open);
		static void expand(AstarNode* node, Grid grid, vector<AstarNode*> &open, vector<AstarNode*> &closed,  Coords end);
        static int heuristic(std::pair<int, int> a, std::pair<int, int>b);
        static bool isValidMove(std::pair<int, int> coord, const Grid &grid);
};




#endif
