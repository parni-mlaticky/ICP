#include "player.h"
#include "wall.h"
#include "ghost.h"
#include "key.h"
#include "finish.h"
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <iostream>
Player::Player(int x, int y, bool isLocal, DrawableItem* item) : Entity(x ,y, item, 'P'), m_local_player(isLocal) {
  m_speed = 5;
  m_key_count = 0;
  m_can_move = true;
  m_type = EntityType::PLAYER;
}

void Player::keyPressEvent(QKeyEvent *event) {
  // Skip movement if this is a remote player.
  int old_dx, old_dy;
  old_dx = this->m_dx;
  old_dy = this->m_dy;
  if (!this->m_local_player)
    return;

  switch (event->key()) {
  case Qt::Key_W:
    setDirection(-1, 0);
    break;
  case Qt::Key_A:
    setDirection(0, -1);
    break;
  case Qt::Key_S:
    setDirection(1, 0);
    break;
  case Qt::Key_D:
    setDirection(0, 1);
    break;
  }
  std::cerr << "direction:" << this->m_dx << " " << this->m_dy << std::endl;
  std::pair<int, int> direction = std::make_pair(this->m_dx, this->m_dy);
  for(auto pair : this->m_allowed_directions){
	if(pair == direction){
		return;
	}
  }
  this->setDirection(old_dx, old_dy);
}

void Player::update() {
}

void Player::addKey() {
  m_key_count++;
}

void Player::onCollision(Entity* other) {
	if(other == this){
		return;
	}
	Ghost* g;
	if((g = dynamic_cast<Ghost*>(other)) != nullptr){
		this->kill();
		return;
	}
	Key* k;
	if((k = dynamic_cast<Key*>(other)) != nullptr){
		this->addKey();
		return;
	}
	Finish* f;
	if((f = dynamic_cast<Finish*>(other)) != nullptr){
		if(f->isOpen()){
			this->m_reached_finish = true;
		}
		return;
	}
}


bool Player::reachedFinish(){
	return this->m_reached_finish;
}

int Player::keyCount(){
	return this->m_key_count;
}
