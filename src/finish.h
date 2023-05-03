#ifndef FINISH_H
#define FINISH_H
#include "entity.h"

class Finish : public Entity {
public:
  Finish(int x, int y, DrawableItem* item);
  bool isOpen();
  void open();
protected:
  bool m_is_open = false;

private:
};
#endif
