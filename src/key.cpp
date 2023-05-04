#include "key.h"
#include "player.h"

Key::Key(int x, int y, DrawableItem* item) : Entity(x, y, item, 'K') {
	this->m_type = EntityType::KEY; 
}

void Key::onCollision(Entity* other){
	if(dynamic_cast<Player*>(other)){
		this->m_is_alive = false;
		return;
	}
}
