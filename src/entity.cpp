#include "entity.h"
#include "level.h"
#include <iostream>
#include <utility>

Entity::Entity(int x, int y) : m_x(x), m_y(y), m_dx(0), m_dy(0) {
  ;
}

void Entity::keyPressEvent(QKeyEvent *event) {
  return;
}

void Entity::update() {}

void Entity::setDirection(int dx, int dy) {
  this->m_dx = dx;
  this->m_dy = dy;
}

std::pair<int, int> Entity::getDxDy() {
	return std::make_pair(this->m_dx, this->m_dy);
}

void Entity::stop() {
  this->m_dx = 0;
  this->m_dy = 0;
}

std::pair<int, int> Entity::get_xy(){
	return std::make_pair(this->m_x, this->m_y);
}


void Entity::set_xy(int x, int y){
	this->m_x = x;
	this->m_y = y;
}

