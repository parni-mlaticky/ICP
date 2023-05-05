#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QObject>
#include "entity.h"

class Ghost : public Entity {
public:
  Ghost(int x, int y, DrawableItem* item, int id);
  void update() override;
private:
  void newDirection();
  int m_steps_left;

};
#endif
