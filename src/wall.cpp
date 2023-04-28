#include "wall.h"
Wall::Wall(qreal x, qreal y, qreal width, qreal height)
    : Entity(x, y, width, height) {}

void Wall::setImage() {
  QPixmap pixmap("/assets/wall.png");
  setPixmap(pixmap);
}
