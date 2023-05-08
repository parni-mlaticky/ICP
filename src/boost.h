/** 
 * @file boost.h
 * @brief Header for the boost entity
 * @author Vladimír Hucovič
 * */

#include "entity.h"


/** 
 * @class Boost
 * @brief Class for the player boost entity
 * */
class Boost : public Entity {
public:
	/** 
	 * @copydoc Entity::Entity()
	 * */ 
	Boost(int x, int y, DrawableItem* item, int id);
	~Boost();
private:

};

