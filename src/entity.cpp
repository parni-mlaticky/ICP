#include "entity.h"
#include "level.h"
#include <iostream>

Entity::Entity(qreal x, qreal y, std::string sprite_path, Level* level) : m_dx(1), m_dy(0), m_level(level) {
  setFlag(QGraphicsItem::ItemIsFocusable, true);
  QPixmap ghostPixmap(("assets/" + sprite_path).c_str());
  setPixmap(ghostPixmap.scaled(level->scale(), level->scale(), Qt::KeepAspectRatio));
  setPos(x * level->scale(), y * level->scale());
}

void Entity::update() {}

void Entity::updatePosition() {
  setPos(x() + m_dx * m_speed, y() + m_dy * m_speed);
}

void Entity::setDirection(int dx, int dy) {
  this->m_dx = dx;
  this->m_dy = dy;
}
