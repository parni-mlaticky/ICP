#ifndef KEY_H
#define KEY_H
#include "entity.h"

class Key : public Entity {
public:
  Key(int x, int y, DrawableItem* item);

private:
  qreal width;
  qreal height;
};
#endif
