#include "ghost.h"
#include <QKeyEvent>
#include <QPainter>

Ghost::Ghost(qreal x, qreal y, Level* level) : Entity(x, y, "ghost.png", level) {}
