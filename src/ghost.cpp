#include "ghost.h"
#include <QKeyEvent>
#include <QPainter>
#include <iostream>

Ghost::Ghost(int x, int y, DrawableItem* item, int id) : Entity(x, y, item, 'G', id), m_steps_left(1) {
    m_can_move = true;
	m_type = EntityType::GHOST;
    m_allowed_directions = std::vector<std::pair<int, int>>();
}

void Ghost::update() {
    std::cerr << "brih" << std::endl;
    --m_steps_left;

    bool colided = true;
    for (auto dir : m_allowed_directions) {
        if(dir.first == m_dx && dir.second == m_dy) {
            colided = false;
            break;
        }
    }

	std::cerr << "colided: " << colided << std::endl;
	std::cerr << "steps left: " << m_steps_left << std::endl;
	std::cerr << "allowed directions: " << m_allowed_directions.size() << std::endl; 
    if (m_steps_left <= 0 || colided) {
        newDirection();
    }
}

void Ghost::newDirection() {
    if (m_allowed_directions.size() == 0) {return;}
    int r = rand() % m_allowed_directions.size();
    m_steps_left = (rand() % 5);

    auto direction = m_allowed_directions[r];
	
    m_dx = direction.first;
    m_dy = direction.second;
	std::cerr << "new direction: " << m_dx << " " << m_dy << std::endl;
}
