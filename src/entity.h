#ifndef ENTITY_H_
#define ENTITY_H_

#include <QKeyEvent>
#include "drawable_item.h"
#include "drawable_item.h"

class Level;

enum EntityType{
  PLAYER = 'P',
  GHOST = 'G',
  KEY = 'K',
  FINISH = 'F',
  WALL = 'X',
  BOOST = 'B',
  HEALTH = 'H',
};

class Entity {
public:
  Entity(int x, int y, DrawableItem* item, char debug_char, int id);
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
  EntityType m_type;
  void setAllowedDirections(std::vector<std::pair<int, int>> directions);
  int getId();
  int getSpeed();
protected:
  int m_id;
  int m_x, m_y;
  int m_dx, m_dy;
  int m_speed;
  bool m_is_alive = true;
  bool m_can_move = false;
  std::vector<std::pair<int, int>> m_allowed_directions;
};

#endif
