#include "player.h"
#include <QKeyEvent>
#include <QPainter>
#include <iostream>

Player::Player(qreal x, qreal y, bool isLocal, Level* level) : Entity(x, y, "player.png", level), m_local_player(isLocal) {
  m_speed = 5;
  setFlag(QGraphicsItem::ItemIsFocusable, true);
  setFocus();
}

void Player::keyPressEvent(QKeyEvent *event) {
  // Skip movement if this is a remote player.
  if (!this->m_local_player) return;

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

void Player::update() {
  ((Entity*) this)->updatePosition();
}
