#ifndef FINISH_H
#define FINISH_H
#include "entity.h"

class Finish : public Entity {
public:
  Finish(qreal x, qreal y, qreal width, qreal height);

  void setImage();

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
