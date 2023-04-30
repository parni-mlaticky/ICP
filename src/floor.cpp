#include "floor.h"

Floor::Floor(qreal x, qreal y, Level* level) : Entity(x, y, "floor.png", level) {
    this->setZValue(-1);
}
