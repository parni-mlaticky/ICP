/** 
 * @file health.cpp
 * @brief Implementation of the Health entity
 * @authors Vladimír Hucovič
 * */

#include "health.h"

Health::Health(int x, int y, DrawableItem* item, int id) : Entity(x, y, item, id) {
	this->m_type = EntityType::HEALTH;
}
