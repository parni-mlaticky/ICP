#include "aStar.h"
#include <iostream>

bool Astar::isValidMove(std::pair<int, int> coord, const Grid &grid) {
    int x = coord.first;
    int y = coord.second;
    // FIXME
    if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size()) {
        return false;
    }

    const auto& cell = grid[x][y];
    for (const Entity *entity : cell) {
        if (entity->m_type == EntityType::WALL) {
            return false;
        }
    }

    return true;
}


int getH(Coords a, Coords b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}


AstarNode* Astar::findLowest(std::vector<AstarNode*> open){
	AstarNode* lowest = open[0];
	for(int i = 0; i < open.size(); i++){
		if(open[i]->f < lowest->f){
			lowest = open[i];
		}
	}
	return lowest;
}


AstarNode* Astar::findInOpen(Coords coords, std::vector<AstarNode*> &open){
	for(int i = 0; i < open.size(); i++){
		if(open[i]->coords == coords){
			return open[i];
		}
	}
	return nullptr;
}

bool isInClosed(Coords coords, vector<AstarNode*> &closed){
	for(int i = 0; i < closed.size(); i++){
		if(closed[i]->coords == coords){
			return true;
		}
	}
	return false;
}

void Astar::expand(AstarNode* node, Grid grid, vector<AstarNode*> &open, vector<AstarNode*> &closed,  Coords end){
	Coords coords = node->coords;
	vector<Coords> neighbours = {
		{coords.first + 1, coords.second},
		{coords.first - 1, coords.second},
		{coords.first, coords.second + 1},
		{coords.first, coords.second -1}
	};
	for(int i = 0; i < neighbours.size(); i++){
		if(isValidMove(neighbours[i], grid)){
			if(isInClosed(neighbours[i], closed)){
				continue;
			}
			AstarNode* newNode = new AstarNode(neighbours[i]);
			newNode->g = node->g + 1;
			newNode->h = getH(neighbours[i], end);
			newNode->f = newNode->g + newNode->h;
			newNode->parent = node;
			AstarNode* existing = findInOpen(newNode->coords, open);
			if(!existing){
				open.push_back(newNode);
				continue;
			}
			if(existing->f < newNode->f){
				continue;
			}
			else{
				auto it = find(open.begin(), open.end(), existing);
				open.erase(it);
				open.push_back(newNode);
			}
		}
	}
}

std::vector<Coords> Astar::calculatePath(Coords start, Coords end, Grid grid){
	vector<AstarNode*> open;
	vector<AstarNode*> closed;
	AstarNode* first = new AstarNode(start);
	open.push_back(first);
	while(!open.empty()){
		AstarNode* lowest = findLowest(open);
		if(lowest->coords == end){
			return lowest->reconstructPath();
		}
		auto it = find(open.begin(), open.end(), lowest);
		open.erase(it);
		closed.push_back(lowest);
		expand(lowest, grid, open, closed, end);
	}
	return {};
}
