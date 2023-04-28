#include "ghost.h"
#include <QKeyEvent>
#include <QPainter>

Ghost::Ghost(qreal x, qreal y, qreal width, qreal height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;

  QPixmap ghostPixmap("../assets/ghost.png");
  setPixmap(ghostPixmap.scaled(width, height, Qt::KeepAspectRatio));
  setPos(x, y);
}

void Ghost::setDirection(int dx, int dy) {
  m_dx = dx;
  m_dy = dy;
}

void Ghost::updatePosition() {
  setPos(this->x + m_dx * m_speed, this->y + m_dy * m_speed);
}
