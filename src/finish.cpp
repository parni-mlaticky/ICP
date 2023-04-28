#include "finish.h"
Finish::Finish(qreal x, qreal y, qreal width, qreal height)
    : Entity(x, y, width, height) {
  QPixmap pixmap("../assetes/finish.png");
  setPixmap(pixmap);
}
