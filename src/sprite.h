#ifndef SPRITE_H_
#define SPRITE_H_

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <utility>
#include "drawable_item.h"

class Scene;

class Sprite : public QObject, public QGraphicsPixmapItem, public DrawableItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
  Sprite(std::string sprite_path);
  void setSpriteScale(int scale);
  void interpolate(int frame_count);
  void setZ(int z);

  // Drawable Item
  void moveTowards(std::pair<int, int>) override;
  void setPosition(std::pair<int, int>) override;

protected:
  QPixmap m_pixmap;
  std::string sprite_path;
  std::pair<int, int> old_coords;
  std::pair<int, int> new_coords;
};

#endif // SPRITE_H_
