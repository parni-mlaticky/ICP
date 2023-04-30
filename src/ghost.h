#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QObject>
#include "entity.h"

class Ghost : public Entity {
public:
  Ghost(qreal x, qreal y, Level* level);
};
#endif
