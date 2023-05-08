/** 
 * @file wall.h
 * @brief Header for the Wall entity
 * @authors Ondřej Zobal
 * */


#ifndef WALL_H
#define WALL_H
#include "entity.h"


/** 
 * @class Wall
 * @brief Class for the wall entity
 * */
class Wall : public Entity {
// public methods
public:
  /** 
   * @copydoc Entity::Entity(int x, int y, DrawableItem* item, int id)
   * */
  Wall(int x, int y, DrawableItem* item, int id);

};
#endif
