#include "key.h"

Key::Key(int x, int y, DrawableItem* item, int id) : Entity(x, y, item, id) {
	this->m_type = EntityType::KEY;
}
