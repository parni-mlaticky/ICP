#ifndef KEY_H
#define KEY_H
#include "entity.h"

class Key : public Entity {
public:
  Key(qreal x, qreal y, qreal width, qreal height);

protected:
  bool collidesWith(const QGraphicsRectItem *otherItem,
                    Qt::ItemSelectionMode mode) const;

private:
  qreal x;
  qreal y;
  qreal width;
  qreal height;
};
#endif
