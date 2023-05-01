#ifndef FINISH_H
#define FINISH_H
#include "entity.h"

class Finish : public Entity {
public:
  Finish(int x, int y);

protected:
  bool collidesWith(const QGraphicsRectItem *otherItem,
                    Qt::ItemSelectionMode mode) const;

private:
};
#endif
