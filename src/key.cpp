#include "key.h"
Key::Key(qreal x, qreal y, qreal width, qreal height)
    : Entity(x, y, width, height) {}

void Key::setImage() {
  QPixmap pixmap("/assets/key.png");
  setPixmap(pixmap);
}
