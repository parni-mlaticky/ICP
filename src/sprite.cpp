#include "sprite.h"

Sprite::Sprite(std::string sprite_path, int animation_frames) : m_current_animation_frame(1),
                                                                m_animation_frames(animation_frames),
                                                                m_scale(-1),
                                                                m_sprite_path(sprite_path),
                                                                m_animate(false),
                                                                m_sprite_variant("") {

  setFlag(QGraphicsItem::ItemIsFocusable, true);
  this->m_sprite_path = sprite_path;
}

void Sprite::setZ(int z) {
  this->setZValue(z);
}

void Sprite::setSpriteScale(int scale) {
  this->m_scale = scale;
  //setPixmap(m_pixmap.scaled(scale, scale, Qt::KeepAspectRatio));
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

void Sprite::setAnimate(bool allow) {
  this->m_animate = allow;
}

void Sprite::animate() {
  QPixmap pixmap;
  auto temp = m_sprite_variant == "" ? "" : "-" + m_sprite_variant;
  std::string name = m_sprite_path + temp + std::to_string(m_current_animation_frame);
  int n = QPixmapCache::find(name.c_str(), &pixmap);

  // If pixmap wasn't cached, load it.
  if (!n) {
    std::cerr << "SPRITE: caching sprite " << name << std::endl;
    pixmap = QPixmap(("assets/" + name + ".png").c_str());
    pixmap = pixmap.scaled(m_scale, m_scale, Qt::KeepAspectRatio);
    QPixmapCache::insert(name.c_str(), pixmap);
  }

  setPixmap(pixmap);

  if (m_animate) {
    if (++m_current_animation_frame > m_animation_frames) {
      m_current_animation_frame = 1;
    }
  }
}

void Sprite::moveTowards(std::pair<int, int> coords) {
  old_coords = new_coords;

  new_coords = coords;
}

void Sprite::setRotation(int dx, int dy) {
  dy = dy == 1 ? 2 : dy;

  QPointF center = this->boundingRect().center();
  QTransform transform;
  transform.translate(center.x(), center.y());
  transform.rotate(90 * dx + 180 * dy);
  transform.translate(-center.x(), -center.y());

  this->setTransform(transform);
  this->setTransformOriginPoint(this->boundingRect().center());
}

void Sprite::setSpriteVariant(std::string variant) {
  m_sprite_variant = variant;
  std::cerr << "Variant set " << variant << std::endl;
}

void Sprite::setSpriteVariant() {
  m_sprite_variant = "";
}
