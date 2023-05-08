/** 
 * @file finish.cpp
 * @brief Implementation of the Finish entity
 * @authors Vladimír Hucovič, Ondřej Zobal
 * */


#include "finish.h"

Finish::Finish(int x, int y, DrawableItem* item, int id) : Entity(x, y, item, id) {
	this->m_type = EntityType::FINISH;
}

bool Finish::isOpen(){
	return this->m_is_open;
}

void Finish::open(){
	this->m_is_open = true;
	this->m_drawable_item->setSpriteVariant("open");
}

void Finish::close(){
	this->m_is_open = false;
	this->m_drawable_item->setSpriteVariant("");
}
