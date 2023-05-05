#include "finish.h"

Finish::Finish(int x, int y, DrawableItem* item, int id) : Entity(x, y, item, 'F', id) {
	this->m_type = EntityType::FINISH;
}

bool Finish::isOpen(){
	return this->m_is_open;
}

void Finish::open(){
	this->m_is_open = true;
}
