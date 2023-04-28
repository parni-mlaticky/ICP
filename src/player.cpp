#include "player.h"
#include <QKeyEvent>
#include <QPainter>

Player::Player() : m_dx(0), m_dy(0), m_speed(5) {
  setFlag(QGraphicsItem::ItemIsFocusable, true);
  setFocus();
  QPixmap playerPixmap("../assets/player.png");
  setPixmap(playerPixmap.scaled(20, 20, Qt::KeepAspectRatio));
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
