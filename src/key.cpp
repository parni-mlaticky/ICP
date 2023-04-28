#include "key.h"
Key::Key(qreal x, qreal y, qreal width, qreal height)
    : Entity(x, y, width, height) {
  QPixmap pixmap("../assets/key.png");
  setPixmap(pixmap);
}
