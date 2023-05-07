#include "entity.h"

Entity::Entity(int x, int y, DrawableItem* item, int id) : m_x(x),
  m_y(y), m_dx(0), m_dy(0), m_drawable_item(item), m_id(id) {
  this->m_allowed_directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
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

bool Entity::canMove(){
	return this->m_can_move;
}

void Entity::kill(){
	this->m_is_alive = false;
}

void Entity::onCollision(Entity* other){
	return;
}

bool Entity::isAlive(){
	return this->m_is_alive;
}

void Entity::setAllowedDirections(std::vector<std::pair<int, int>> directions) {
    m_allowed_directions = directions;
}

int Entity::getId() {
  return this->m_id;
}

