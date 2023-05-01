#ifndef FINISH_H
#define FINISH_H
#include "entity.h"

class Finish : public Entity {
public:
  Finish();

protected:
  bool collidesWith(const QGraphicsRectItem *otherItem,
                    Qt::ItemSelectionMode mode) const;

private:
};
#endif
