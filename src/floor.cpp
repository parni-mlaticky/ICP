#include "floor.h"

Floor::Floor(qreal x, qreal y) : Entity(x, y, "floor.png") {
    this->setZValue(-1);
}
