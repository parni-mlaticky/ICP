#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QObject>

class Ghost : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  Ghost(qreal x, qreal y, qreal width, qreal height);

  void setDirection(int dx, int dy);

  void updatePosition();

private:
  int m_dx, m_dy;
  int m_speed = 5;
  qreal width;
  qreal height;
  qreal x;
  qreal y;
};
#endif
