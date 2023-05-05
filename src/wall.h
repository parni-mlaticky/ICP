#ifndef WALL_H
#define WALL_H
#include "entity.h"

class Wall : public Entity {
public:
  Wall(int x, int y, DrawableItem* item, int id);

};
#endif
