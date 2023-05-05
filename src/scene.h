#ifndef SCENE_H_
#define SCENE_H_

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "sprite.h"
#include "drawable.h"
#include <utility>
#include <QGraphicsScene>
#include <vector>

class MainWindow;

class Scene : public Drawable, public QGraphicsScene {
public:
  // Drawable
  void render(int frame_n);
  DrawableItem* drawItem(std::string sprite_path) override;
  void deleteItem(DrawableItem* item) override;
  void setGridDimensions(int x, int y) override;
  void moveTowards(DrawableItem* item, int row, int col) override;
  void setPosition(DrawableItem* item, int row, int col) override;
  void drawBackgroundTiles(std::string sprite_path) override;
  void setKeyCount(int count) override;
  void setHealthCount(int count) override;

  Scene(int m_window_w, int m_window_h, int frame_between_updates, MainWindow* window);
  std::pair<int, int> translate(int x, int y);
  int scale();

protected:
  void keyPressEvent(QKeyEvent* event) override;
  void addBackgroundFloor(int x, int y);
  MainWindow* m_window;
  int m_update_grid;
  int m_update_grid_counter;
  int m_scale;
  int m_window_w;
  int m_window_h;
  int m_x;
  int m_y;
  int keyCount;
  int healthCount;
  std::vector<Sprite *> healthSprites;
  std::vector<Sprite *> keySprites;
};

#endif
