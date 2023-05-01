#ifndef CELL_H_
#define CELL_H_

#include "entity.h"

class Level;

class Cell {
private:
	Entity* entity;
	Level* level;
public:
	Cell(Entity* entity, Level* level);
	Entity* getEntity();
	void setEntity(Entity* entity);
	void updateSprite(int row, int col);
};

#endif
