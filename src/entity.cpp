#include "entity.h"
#include "level.h"
#include <iostream>

Entity::Entity(std::string sprite_path) : m_dx(0), m_dy(0) {
  setFlag(QGraphicsItem::ItemIsFocusable, true);
  this->m_pixmap = QPixmap (("assets/" + sprite_path).c_str());
  setPos(0, 0);
  this->sprite_path = sprite_path;
}

void Entity::setSpriteScale(int scale) {
  setPixmap(m_pixmap.scaled(scale, scale, Qt::KeepAspectRatio));
}

void Entity::update() {}

void Entity::updatePosition() {

}

void Entity::updateSprite(int col, int row, Level* level) {
  auto coords = level->translate(col, row);
  setPos(coords.first, coords.second);
}

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
