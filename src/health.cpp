#include "health.h"

Health::Health(int x, int y, DrawableItem* item, int id) : Entity(x, y, item, 'H', id) {
	this->m_type = EntityType::HEALTH;
}
