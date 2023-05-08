/** 
 * @file scene.h
 * @brief Header for the Scene class
 * @authors Ondřej Zobal, Petr Kolouch, Vladimír Hucovič
 * */

#ifndef SCENE_H_
#define SCENE_H_

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "sprite.h"
#include "drawable.h"
#include <utility>
#include <QGraphicsScene>
#include <vector>
#include "drawable_item.h"
#include <utility>
#include <iostream>
#include <QPixmapCache>
#include <QDir>
class MainWindow;

/**
  * @brief A graphical class for drawing on the screen
  * */
class Scene : public Drawable, public QGraphicsScene {
public:
  // Drawable
  // See drawable.h for comments.
  void render(int frame_n) override;
  DrawableItem* drawItem(std::string sprite_path, int frame_count, rotationType rType) override;
  void deleteItem(DrawableItem* item) override;
  void setGridDimensions(int x, int y) override;
  void moveTowards(DrawableItem* item, int row, int col) override;
  void setPosition(DrawableItem* item, int row, int col) override;
  void drawBackgroundTiles(std::string sprite_path) override;
  void setKeyCount(int count) override;
  void setHealthCount(int count) override;
  std::pair<int, int> reverseTranslate(int x, int y) override;

  /**
   * @brief Function invoked by clicking the mouse
   * @param event Information about the keypress
   * */
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  /**
   * @param m_window_w With of the scene
   * @param m_window_h Height of the scene
   * @param frame_between_updates How many renders an interpolation should take
   * @param window Window to draw in
   * */
  Scene(int m_window_w, int m_window_h, int frame_between_updates, MainWindow* window);
  /**
   * @brief Translates gird coordinates to pixel coordinates
   * @param x X coordinate
   * @param y Y coordinate
   * @return Pair of X and Y pixel coordinates
   * */
  std::pair<int, int> translate(int x, int y);
  /**
   * @brief Scale calculated from the window dimenstions and and grid size
   * @return Size of each grid cell in pixels
   * */
  int scale();

protected:
  /**
   * @brief Caches all sprites
   * @param dirPath Path to directory contating the sprites that should be cached
   * */
  void cacheSprites(const std::string dirPath);
  /**
   * @brief Handles sending messages
   * @param The message that will be sent to the other connected party.
   * */
  void keyPressEvent(QKeyEvent* event) override;
  /**
   * @brief Adds floor tile to the background
   * @param x X coordinate
   * @param y Y coordinate
   * */
  void addBackgroundFloor(int x, int y);
  /**
   * @brief Reference to the window where we are drawing
   * */
  MainWindow* m_window;
  /**
   * @brief Frames that an interpolation should take
   * */
  int m_update_grid;
  /**
   * @brief Current frame count
   * */
  int m_update_grid_counter;
  /**
   * @brief Scale of a single tile in pixels
   * */
  int m_scale;
  /**
   * @brief Window width
   * */
  int m_window_w;
  /**
   * @brief Window height
   * */
  int m_window_h;
  /**
   * @brief Horizontal grid dimenstion
   * */
  int m_x;
  /**
   * @brief Vertical grid dimenstion
   * */
  int m_y;
  /**
   * @brief Counter of key HUD element
   * */
  int keyCount;
  /**
   * @brief Counter of health HUD element
   * */
  int healthCount;
  int healthOffset;
  /**
   * @brief Offset of the key from the edge of the screen
   * */
  int keyOffset;
  /**
   * @brief HUD health sprites
   * */
  std::vector<Sprite *> healthSprites;
  /**
   * @brief HUD key sprites
   * */
  std::vector<Sprite *> keySprites;
};

#endif
