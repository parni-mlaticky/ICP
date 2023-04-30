#ifndef LEVEL_H_
#define LEVEL_H_

#include <QGraphicsScene>
#include "entity.h"
#include <vector>
#include "cell.h"


class Level : public QObject {
  Q_OBJECT
public:
  Level(QGraphicsScene *scene, int window_w, int window_h);
  void loadLevel(const QString &filename);
  void addEntity(char c, int x, int y);
  void updateScene();
  int scale();
  void dumpGrid();


private:
  std::vector<std::vector<Cell*> > m_grid;
  Entity* createEntity(char c, int x, int y);
  QGraphicsScene *m_scene;
  int m_scale;
  int m_window_w;
  int m_window_h;
};

#endif
