#include "entity.h"
#include "level.h"
#include <iostream>

Entity::Entity(qreal x, qreal y, std::string sprite_path) : m_dx(1), m_dy(0) {
  setFlag(QGraphicsItem::ItemIsFocusable, true);
  this->m_pixmap = QPixmap (("assets/" + sprite_path).c_str());
  setPos(x, y);
  this->sprite_path = sprite_path;
  setDirection(0, 0);
}

void Entity::setSpriteScale(int scale) {
  setPixmap(m_pixmap.scaled(scale, scale, Qt::KeepAspectRatio));
}

void Entity::update() {}

void Entity::updatePosition() {
  setPos(x() + m_dx * m_speed, y() + m_dy * m_speed);
}

void Entity::setDirection(int dx, int dy) {
  this->m_dx = dx;
  this->m_dy = dy;
}

std::pair<int, int> Entity::getDxDy() {
	return std::make_pair(this->m_dx, this->m_dy);
}
