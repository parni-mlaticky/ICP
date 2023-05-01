#include "entity.h"
#include "level.h"
#include <iostream>
#include <utility>

Entity::Entity(std::string sprite_path, int x, int y) : m_x(x), m_y(y), m_dx(0), m_dy(0) {
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
  old_coords = coords;
  new_coords = coords;
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

std::pair<int, int> Entity::get_xy(){
	return std::make_pair(this->m_x, this->m_y);
}


void Entity::set_xy(int x, int y){
	this->m_x = x;
	this->m_y = y;
}

void Entity::interpolate(int in_frames) {
  int delta_x = new_coords.first - old_coords.first;
  int delta_y = new_coords.second - old_coords.second;

  int frame_delta_x = delta_x * (1./(double)in_frames);
  int frame_delta_y = delta_y * (1./(double)in_frames);

  setPos(x() + frame_delta_x, y() + frame_delta_y);
}

void Entity::move_to(int x, int y, Level* level) {
  auto coords = level->translate(x, y);

  old_coords = new_coords;

  new_coords = coords;
}
