#ifndef DRAWABLE_ENTITY_H_
#define DRAWABLE_ENTITY_H_

#include <utility>
#include <string>

class DrawableItem {
public:
  virtual void moveTowards(std::pair<int, int> coords) = 0;
  virtual void setPosition(std::pair<int, int> coords) = 0;
  virtual void setRotation(int dx, int dy) = 0;
  virtual void setAnimate(bool allow) = 0;
  virtual void setSpriteVariant(std::string variant) = 0;
  virtual void setSpriteVariant() = 0;
  DrawableItem();
};

#endif // DRAWABLE_ENTITY_H_
