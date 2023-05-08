/**
 *
 * @file health.h
 * @brief Header of the Health entity
 * @authors Vladimír Hucovič
 * */

#include "entity.h"


class Health : public Entity {
// public methods
public:
	/** 
	 * @copydoc Entity::Entity(int x, int y, DrawableItem* item, int id)
	 * */
	Health(int x, int y, DrawableItem* item, int id);
private:

};
