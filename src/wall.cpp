#include "wall.h"
Wall::Wall(qreal x, qreal y, qreal width, qreal height)
    : Entity(x, y, width, height) {

  QPixmap pixmap("../assets/wall.png");
  setPixmap(pixmap);
}
