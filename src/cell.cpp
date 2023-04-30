#include "cell.h"
#include "level.h"


Cell::Cell(Entity* entity, Level* level) {
	this->entity = entity;
	this->level = level;
}

Entity* Cell::getEntity() {
	return this->entity;
}

void Cell::setEntity(Entity* entity) {
	this->entity = entity;
}

void Cell::updateSprite(int row, int col) {
	auto coord = level->translate(row, col);
	this->entity->setPos(coord.first, coord.second);
}
