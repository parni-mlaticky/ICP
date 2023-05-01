#ifndef ENTITY_H_
#define ENTITY_H_

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Level;

class Entity : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
  Entity(std::string sprite_path);
  virtual void update();
  void setDirection(int dx, int dy);
  void updatePosition();
  void setSpriteScale(int scale);
  std::string sprite_path;
  std::pair<int, int> getDxDy();	
  void updateSprite(int col, int row, Level* level);
  void stop();
public slots:

protected:
    int m_dx, m_dy;
    int m_speed;
    QPixmap m_pixmap;
};

#endif
