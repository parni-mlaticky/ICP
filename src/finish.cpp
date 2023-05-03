#include "finish.h"

Finish::Finish(int x, int y, DrawableItem* item) : Entity(x, y, item, 'F') {

}

bool Finish::isOpen(){
	return this->m_is_open;
}

void Finish::open(){
	this->m_is_open = true;
}
