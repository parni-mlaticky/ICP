#ifndef LEVEL_H_
#define LEVEL_H_

#include <utility>
#include <QGraphicsScene>
#include "drawable.h"
#include "entity.h"
#include <vector>
#include <QKeyEvent>
#include "player.h"
#include "key.h"

using EntityVector = std::vector<Entity*>;
using Row = std::vector<EntityVector>;
using Grid = std::vector<Row>;

class Level {
public:
  Level(Drawable* drawable);
  void loadLevel(const QString &filename);
  void addEntity(Entity* entity);
  void updateScene();
  int scale();
  void dumpGrid();
  std::pair<int, int> translate(int x, int y);
  void updateGrid();
  bool checkWall(int x, int y);
  std::pair<Player*, Key*> checkPlayerKeyPickup();
  void keyPressEvent(QKeyEvent* event);

  template<typename T>
  std::vector<T*> findEntities();

  template<typename T>
  T* findEntityAt(int x, int y);

  bool removeEntity(Entity* ent);
  void updateLevel();

private:
  Grid m_grid;
  EntityVector m_background_gfx;
  Entity* createEntity(char c, int x, int y);
  void displayGrid();
  void addBackgroundFloor(int x, int y);
  int m_bound_x;
  int m_bound_y;
  Drawable* m_drawable;
};

#endif
