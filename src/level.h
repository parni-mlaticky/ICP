#ifndef LEVEL_H_
#define LEVEL_H_

#include <utility>
#include <QGraphicsScene>
#include "entity.h"
#include <vector>


class Level : public QObject {
  Q_OBJECT
public:
  Level(QGraphicsScene *scene, int window_w, int window_h);
  void loadLevel(const QString &filename);
  void addEntity(Entity* entity);
  void updateScene();
  int scale();
  void dumpGrid();
  std::pair<int, int> translate(int x, int y);
  void updateGrid();
  bool checkWall(int x, int y);

private:

  std::vector<std::vector<Entity*> > m_grid;
  std::vector<Entity*> m_background_gfx;
  Entity* createEntity(char c);
  QGraphicsScene *m_scene;
  void displayGrid();
  void addBackgroundFloor(int x, int y);
  int m_scale;
  int m_window_w;
  int m_window_h;
  int m_bound_x;
  int m_bound_y;
};

#endif
