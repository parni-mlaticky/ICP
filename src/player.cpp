#include "player.h"
#include <QKeyEvent>
#include <QPainter>

Player::Player() : m_dx(0), m_dy(0), m_speed(5) {
  setFlag(QGraphicsItem::ItemIsFocusable, true);
  setFocus();
}

QRectF Player::boundingRect() const { return QRectF(-10, -10, 20, 20); }

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
  painter->setBrush(Qt::blue);
  painter->drawEllipse(boundingRect());
}

void Player::setDirection(int dx, int dy) {
  m_dx = dx;
  m_dy = dy;
}

void Player::updatePosition() {
  setPos(x() + m_dx * m_speed, y() + m_dy * m_speed);
}

void Player::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_W:
    setDirection(0, -1);
    break;
  case Qt::Key_A:
    setDirection(-1, 0);
    break;
  case Qt::Key_S:
    setDirection(0, 1);
    break;
  case Qt::Key_D:
    setDirection(1, 0);
    break;
  }
}
