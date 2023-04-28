#include "finish.h"
Finish::Finish(qreal x, qreal y, qreal width, qreal height)
    : Entity(x, y, width, height) {}

void Finish::setImage() {
  QPixmap pixmap("/assets/finish.png");
  setPixmap(pixmap);
}
