#include "ghost.h"
#include <QKeyEvent>
#include <QPainter>

Ghost::Ghost(qreal x, qreal y, qreal width, qreal height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

QRectF Ghost::boundingRect() const { return QRectF(-10, -10, 20, 20); }

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
  painter->setBrush(Qt::red);
  painter->drawEllipse(boundingRect());
}

void Ghost::setDirection(int dx, int dy) {
  m_dx = dx;
  m_dy = dy;
}

void Ghost::updatePosition() {
  setPos(this->x + m_dx * m_speed, this->y + m_dy * m_speed);
}
