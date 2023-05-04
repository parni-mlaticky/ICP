#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "drawable_item.h"
#include <string>

class Drawable {
public:
  virtual void render(int frame_n) = 0;
  virtual DrawableItem* drawItem(std::string sprite_path) = 0;
  virtual void deleteItem(DrawableItem* item) = 0;
  virtual void setGridDimensions(int x, int y) = 0;
  virtual void drawBackgroundTiles(std::string sprite_path) = 0;

  virtual void moveTowards(DrawableItem* item, int row, int col) = 0;
  virtual void setPosition(DrawableItem* item, int row, int col) = 0;

  Drawable();
};

#endif // DRAWABLE_H_
