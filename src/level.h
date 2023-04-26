#include <QGraphicsScene>

const int GRID_SIZE = 40;

class Level {
public:
  Level(QGraphicsScene *scene);
  void loadLevel(const QString &filename);
  QPointF getStartingPoint();
  QPointF getFinishPoint();

private:
  void addEntity(char entityType, int x, int y);

  QGraphicsScene *m_scene;
  QPointF m_startingPoint;
  QPointF m_finishPoint;
};
