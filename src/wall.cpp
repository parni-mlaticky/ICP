#include "wall.h"

Wall::Wall(int x, int y, DrawableItem* item) : Entity(x, y, item, 'X') {
	this->m_type = EntityType::WALL;
}
