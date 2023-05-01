#include "player.h"
#include "wall.h"
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <iostream>
Player::Player(int x, int y, bool isLocal) : Entity("player.png", x ,y), m_local_player(isLocal) {
  m_speed = 5;
  setFlag(QGraphicsItem::ItemIsFocusable, true);
  setFocus();
}

void Player::keyPressEvent(QKeyEvent *event) {
  // Skip movement if this is a remote player.
  if (!this->m_local_player)
    return;

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
  std::cerr << "direction:" << this->m_dx << " " << this->m_dy << std::endl;
}

void Player::update() {
  this->updatePosition();
  this->setFocus();
  // std::cerr << "x " << x() << " y " << y() << std::endl;
}
