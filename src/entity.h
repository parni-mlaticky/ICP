#ifndef ENTITY_H_
#define ENTITY_H_

#include <QKeyEvent>
#include "drawable_item.h"

class Level;

class Entity {
public:
  Entity(int x, int y);
  virtual void update();
  void setDirection(int dx, int dy);
  void updatePosition();
  std::pair<int, int> getDxDy();
  void stop();
  std::pair<int, int> get_xy();
  void set_xy(int x, int y);
  DrawableItem* m_drawableItem;

protected:
  virtual void keyPressEvent(QKeyEvent *event);
	int m_x, m_y;
  int m_dx, m_dy;
  int m_speed;
};

#endif
