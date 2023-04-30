#include "cell.h"


Cell::Cell(Entity* entity) {
	this->entity = entity;
}

Entity* Cell::getEntity() {
	return this->entity;
}

void Cell::setEntity(Entity* entity) {
	this->entity = entity;
}


