/** 
 * @file ghost.cpp
 * @brief Implementation of the Ghost entity
 * @authors Ondřej Zobal
 * */


#include "ghost.h"

Ghost::Ghost(int x, int y, DrawableItem* item, int id) : Entity(x, y, item, id), m_steps_left(1) {
    m_can_move = true;
	m_type = EntityType::GHOST;
    m_allowed_directions = std::vector<std::pair<int, int>>();
}

void Ghost::update() {
    --m_steps_left;
	
    bool colided = true;
    for (auto dir : m_allowed_directions) {
        if(dir.first == m_dx && dir.second == m_dy) {
            colided = false;
            break;
        }
    }

    if (m_steps_left <= 0 || colided) {
        newDirection();
    }
}


void Ghost::newDirection() {
    if (m_allowed_directions.size() == 0) {return;}
	// pick a random direction from those allowed
    int r = rand() % m_allowed_directions.size();
	// pick the number of steps to go in that direction
    m_steps_left = (rand() % 5);

    auto direction = m_allowed_directions[r];
	
    m_dx = direction.first;
    m_dy = direction.second;
}
