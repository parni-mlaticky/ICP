#ifndef FINISH_H
#define FINISH_H
#include "entity.h"


/**
 * @class Finish
 * @brief Class for the finish (target) entity
 */
class Finish : public Entity {
// private members
private:
  /** 
   * @brief True if the finish is open
   * */
  bool m_is_open = false;

// public methods
public:
  /**
   * @copydoc Entity::Entity(int x, int y, DrawableItem* item, int id)
   * */
  Finish(int x, int y, DrawableItem* item, int id);
  /** 
   * @brief Returns true if the finish is open
   * */
  bool isOpen();
  /** 
   * @brief Opens the finish
   * */
  void open();

private:
};
#endif
