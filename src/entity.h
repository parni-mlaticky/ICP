#ifndef ENTITY_H_
#define ENTITY_H_

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Level;

class Entity : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
  Entity(qreal x, qreal y, std::string sprite_path, Level* level);
  virtual void update();
  void setDirection(int dx, int dy);

public slots:
  void updatePosition();

protected:
    std::string sprite_path;
    int m_dx, m_dy;
    int m_speed;
    Level* m_level;
};

#endif
