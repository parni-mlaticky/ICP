#include "sprite.h"

Sprite::Sprite(std::string sprite_path) {
  setFlag(QGraphicsItem::ItemIsFocusable, true);
  this->m_pixmap = QPixmap (("assets/" + sprite_path).c_str());
  this->sprite_path = sprite_path;
  setPos(0, 0);
}

void Sprite::setZ(int z) {
  this->setZValue(z);
}

void Sprite::setSpriteScale(int scale) {
  setPixmap(m_pixmap.scaled(scale, scale, Qt::KeepAspectRatio));
}

void Sprite::setPosition(std::pair<int, int> coords) {
  setPos(coords.first, coords.second);
  old_coords = coords;
  new_coords = coords;
}

void Sprite::interpolate(int frame_n, int in_frames) {
  int delta_x = new_coords.first - old_coords.first;
  int delta_y = new_coords.second - old_coords.second;

  int frame_delta_x = delta_x * ((double)frame_n/(double)in_frames);
  int frame_delta_y = delta_y * ((double)frame_n/(double)in_frames);

  setPos(old_coords.first + frame_delta_x, old_coords.second + frame_delta_y);
}

void Sprite::moveTowards(std::pair<int, int> coords) {
  old_coords = new_coords;

  new_coords = coords;
}
