#ifndef ENTITY_H_
#define ENTITY_H_

#include <QKeyEvent>
#include "drawable_item.h"
#include "drawable_item.h"

class Level;

class Entity {
public:
  Entity(int x, int y, DrawableItem* item, char debug_char);
  virtual void update();
  void setDirection(int dx, int dy);
  void updatePosition();
  std::pair<int, int> getDxDy();
  void stop();
  std::pair<int, int> get_xy();
  void set_xy(int x, int y);
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void onCollision(Entity* other);
  char m_debug_char;
  DrawableItem* m_drawable_item;
  bool canMove();
  bool isAlive();
  void kill();

protected:
  int m_x, m_y;
  int m_dx, m_dy;
  int m_speed;
  bool m_is_alive = true;
  bool m_can_move = false;
};

#endif
