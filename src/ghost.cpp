#include "ghost.h"
#include <QKeyEvent>
#include <QPainter>

Ghost::Ghost(int x, int y, DrawableItem* item) : Entity(x, y, item, 'G') {}
