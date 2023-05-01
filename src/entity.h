#ifndef ENTITY_H_
#define ENTITY_H_

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Level;

class Entity : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
  Entity(std::string sprite_path, int x, int y);
  virtual void update();
  void setDirection(int dx, int dy);
  void updatePosition();
  void setSpriteScale(int scale);
  std::string sprite_path;
  std::pair<int, int> getDxDy();	
  void updateSprite(int row, int col, Level* level);
  void stop();
  std::pair<int, int> get_xy();
  void set_xy(int x, int y);
  void interpolate(int in_frames);
  void move_to(int x, int y, Level* level);

public slots:

protected:
	int m_x, m_y;
    int m_dx, m_dy;
    int m_speed;
    QPixmap m_pixmap;
    std::pair<int, int> old_coords;
    std::pair<int, int> new_coords;
};

#endif
