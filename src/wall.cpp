/** 
 * @file wall.cpp
 * @brief Implementation of the Wall entity
 * @authors Ondřej Zobal
 * */


#include "wall.h"

Wall::Wall(int x, int y, DrawableItem* item, int id) : Entity(x, y, item, id) {
	this->m_type = EntityType::WALL;
}
