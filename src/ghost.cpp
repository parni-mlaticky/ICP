#include "ghost.h"
#include <QKeyEvent>
#include <QPainter>
#include <iostream>

Ghost::Ghost(int x, int y, DrawableItem* item) : Entity(x, y, item, 'G'), m_steps_left(1) {
    m_can_move = true;
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

    if (!m_steps_left || colided) {
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
}

void Ghost::setAllowedDirections(std::vector<std::pair<int, int>> directions) {
    m_allowed_directions = directions;
}
