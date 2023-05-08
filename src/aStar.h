/** 
 * @file aStar.h
 * @brief Header file for the A* algorithm
 * @authors Petr Kolouch, Vladimír Hucovič 
**/


#ifndef ASTAR_H_
#define ASTAR_H_
#include "level.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>

using Coords = std::pair<int, int>;


using namespace std;



/** 
 * AstarNode
 * @brief Represents a node in the A* algorithm for finding a path in the level
 * */
struct AstarNode{
	/** 
	 * @brief The coordinates of the node
	 * */
	Coords coords;
	/** 
	 * @brief The f value of the node
	 * */
	int f;
	/** 
	 * @brief The g value of the node
	 * */
	int g;
	/** 
	 * @brief The h value of the node
	 * */
	int h;
	/** 
	 * @brief The parent node of the node
	 * */
	AstarNode* parent;
	/** 
	 * @brief Constructor for the AstarNode
	 * @param coords The coordinates of the node
	 * @param f The f value of the node
	 * @param g The g value of the node
	 * @param h The h value of the node
	 * @param parent The parent node of the node
	 * */
	AstarNode(Coords coords, int f, int g, int h, AstarNode* parent){
		this->coords = coords;
		this->f = f;
		this->g = g;
		this->h = h;
		this->parent = parent;
	}

	/** 
	 * @brief Constructor for the AstarNode, with f,g,h values set to 0 and parent unset
	 * @param coords The coordinates of the node
	 * */
	AstarNode(Coords coords){
		this->coords = coords;
		this->f = 0;
		this->g = 0;
		this->h = 0;
		this->parent = nullptr;
	}
	/** 
	 * @brief Reconstructs the path from this node until the start node
	 * */
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


/** 
 * @class Astar
 * @brief Class for the A* algorithm
 * @details To find the shortest path from one square to another in the grid, this A* algorithm is used.
 * */
class Astar {
    public:
		/** 
		 * @brief Calculates the shortest path from one square to another in the grid
		 * @param start The starting coordinates
		 * @param end The ending coordinates
		 * @param grid The grid to find the path in
		 * @return The shortest path from start to end
		 * */
		static std::vector<Coords> calculatePath(Coords start, Coords end, Grid grid);
		/** 
		 * @brief Finds the lowest f value in the open list
		 * @param open The open list
		 * @return The node with the lowest f value
		 * */
		static AstarNode* findLowest(std::vector<AstarNode*> open);
		/** 
		 * @brief Finds a node (specified by coordinates) in the open list
		 * @param coords The coordinates of the node to find
		 * @param open The open list
		 * @return The node with the given coordinates or nullptr if not found
		 * */
		static AstarNode* findInOpen(Coords coords, std::vector<AstarNode*> &open);
		/** 
		 * @brief Expands the node (finds all neighbours and adds them to the open list with their g,h,f values set)
		 * @param node The node to expand
		 * @param grid The grid to find the path in
		 * @param open The open list
		 * @param closed The closed list
		 * @param end The end coordinates
		 * */
		static void expand(AstarNode* node, Grid grid, vector<AstarNode*> &open, vector<AstarNode*> &closed,  Coords end);
		/**
		 * @brief Calculates the heuristic value of a node
		 * @param a The coordinates of the node
		 * @param b The coordinates of the end node
		 * @return The heuristic value of the node
		 * */
        static int heuristic(Coords a, Coords b);
		/** 
		 * @brief Checks if there is a walkable node at the given coordinate
		 * @param coord The coordinates to check
		 * @param grid The grid to check in
		 * */
        static bool isValidMove(Coords coord, const Grid &grid);
};




#endif

