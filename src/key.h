/**  
 * @file key.h
 * @brief Header of the Key entity
 * @authors Vladimír Hucovič
 * */

#ifndef KEY_H
#define KEY_H
#include "entity.h"
/** 
 * @class Key
 * @brief Class for the key entity
 * */
class Key : public Entity {
// private methods	
public:
  /** 
   * @copydoc Entity::Entity(int x, int y, DrawableItem* item, int id)
   * */
  Key(int x, int y, DrawableItem* item, int id);
};
#endif
