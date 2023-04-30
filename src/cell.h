#include "entity.h"

class Cell {
private:
	Entity* entity;
public:
	Cell(Entity* entity);
	Entity* getEntity();
	void setEntity(Entity* entity);
};
