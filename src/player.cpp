#include "player.h"
#include "entity.h"
#include "wall.h"
#include "ghost.h"
#include "key.h"
#include "finish.h"
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <iostream>
#include <thread>
#include <chrono>
Player::Player(int x, int y, bool isLocal, DrawableItem* item, int id) : Entity(x ,y, item, 'P', id), m_local_player(isLocal) {
  m_speed = 5;
  m_key_count = 0;
  m_can_move = true;
  m_type = EntityType::PLAYER;
}


void Player::boostCountdown(){
  // TODO HACK maybe we should do this in the main thread or add mutex ??
  this->m_drawable_item->setSpriteVariant("enraged");
	while(this->m_boost_seconds_left > 0){
		std::cerr << "boost seconds left: " << this->m_boost_seconds_left << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		this->m_boost_seconds_left--;
	}
  this->m_drawable_item->setSpriteVariant();
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

void Player::onCollision(Entity* other) {
	if(other == this){
		return;
	}
	switch(other->m_type){
		case EntityType::WALL: {
			this->setDirection(0, 0);
			break;	
		}
		case EntityType::GHOST:{
			if(this->m_boost_seconds_left){
				dynamic_cast<Ghost*>(other)->kill();
			}
			else{
				this->kill();
			}
			break;
		}
		case EntityType::KEY: {
				this->m_key_count++;
				break;
		}
		case EntityType::FINISH: {
			if(dynamic_cast<Finish*>(other)->isOpen()){
				this->m_reached_finish = true;
			}
			break;
		}
		case EntityType::BOOST: {
			other->kill();
			if(this->m_boost_seconds_left == 0){
				std::thread t(&Player::boostCountdown, this);
				t.detach();
			}
			this->m_boost_seconds_left += 5;
			break;
		}
		default:
			break;
	}
}


bool Player::reachedFinish(){
	return this->m_reached_finish;
}

int Player::keyCount(){
	return this->m_key_count;
}
