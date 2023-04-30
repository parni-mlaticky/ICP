#ifndef WALL_H
#define WALL_H
#include "entity.h"

class Wall : public Entity {
public:
  Wall(qreal x, qreal y, Level* level);

protected:
  bool collidesWith(const QGraphicsRectItem *otherItem,
                    Qt::ItemSelectionMode mode) const;

};
#endif
