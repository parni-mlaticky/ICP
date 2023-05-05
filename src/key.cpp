#include "key.h"
#include "player.h"

Key::Key(int x, int y, DrawableItem* item, int id) : Entity(x, y, item, 'K', id) {
	this->m_type = EntityType::KEY;
}

void Key::onCollision(Entity* other){
	if(dynamic_cast<Player*>(other)){
		this->m_is_alive = false;
		return;
	}
}
