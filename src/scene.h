#ifndef SCENE_H_
#define SCENE_H_

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "sprite.h"
#include "drawable.h"
#include <utility>
#include <QGraphicsScene>

class MainWindow;

class Scene : public Drawable, public QGraphicsScene {
public:
  // Drawable
  void render();
  DrawableItem* drawEntity(std::string sprite) override;
  void deleteEntity(DrawableItem* item) override;
  void setGridDimensions(int x, int y) override;
  void moveTowards(DrawableItem* item, int col, int row) override;
  void setPosition(DrawableItem* item, int col, int row) override;

  Scene(int m_window_w, int m_window_h, int frame_between_updates, MainWindow* window);
  std::pair<int, int> translate(int x, int y);
  int scale();

protected:
  void addBackgroundFloor(int x, int y);
  MainWindow* m_window;
  int m_update_grid;
  int m_update_grid_counter;
  int m_scale;
  int m_window_w;
  int m_window_h;
  int m_x;
  int m_y;
};

#endif
