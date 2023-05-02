#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QObject>
#include "entity.h"

class Ghost : public Entity {
public:
  Ghost(int x, int y, DrawableItem* item);
  void update() override;
  void setAllowedDirections(std::vector<std::pair<int, int>> directions);
private:
  void newDirection();
  int m_steps_left;
  std::vector<std::pair<int, int>> m_allowed_directions;

};
#endif
