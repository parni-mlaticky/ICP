#ifndef LEVEL_H_
#define LEVEL_H_

#include <QGraphicsScene>
#include "entity.h"
#include <vector>

class Level : public QObject {
  Q_OBJECT
public:
  Level(QGraphicsScene *scene, int window_w, int window_h);
  void loadLevel(const QString &filename);
  void addEntity(char c, qreal x, qreal y);
  void updateScene();
  int scale();


private:
  Entity* createEntity(char c, qreal x, qreal y);
  QGraphicsScene *m_scene;
  int m_scale;
  int m_window_w;
  int m_window_h;
};

#endif
