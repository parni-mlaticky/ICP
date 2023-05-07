#ifndef SPRITE_H_
#define SPRITE_H_

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <utility>
#include "drawable_item.h"
#include <iostream>
#include <QPixmapCache>
#include <qnamespace.h>
#include <qpixmapcache.h>
class Scene;

// TODO Comment

class Sprite : public QObject, public QGraphicsPixmapItem, public DrawableItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
  Sprite(std::string sprite_path, int frame_count);
  void setSpriteScale(int scale);
  void interpolate(int frame_n, int frame_count);
  void setZ(int z);
  void animate();

  // Drawable Item
  void moveTowards(std::pair<int, int>) override;
  void setPosition(std::pair<int, int>) override;
  void setRotation(int dx, int dy) override;
  void setAnimate(bool allow) override;
  void setSpriteVariant(std::string variant) override;
  void setSpriteVariant() override;
protected:
  QPixmap m_pixmap;
  std::string m_sprite_path;
  std::string m_sprite_variant;
  int m_animation_frames;
  int m_current_animation_frame;
  bool m_animate;
  int m_scale;
  std::pair<int, int> old_coords;
  std::pair<int, int> new_coords;
};

#endif // SPRITE_H_
