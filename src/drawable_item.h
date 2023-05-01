#ifndef DRAWABLE_ENTITY_H_
#define DRAWABLE_ENTITY_H_

#include <utility>

class DrawableItem {
public:
    virtual void moveTowards(std::pair<int, int> coords) = 0;
    virtual void setPosition(std::pair<int, int> coords) = 0;
  DrawableItem();
};

#endif // DRAWABLE_ENTITY_H_
