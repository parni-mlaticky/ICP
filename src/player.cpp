#include "player.h"

Player::Player(int x, int y, bool isLocal, DrawableItem* item, int id) : Entity(x ,y, item, id), m_local_player(isLocal) {
  m_key_count = 0;
  m_can_move = true;
  m_type = EntityType::PLAYER;
  m_health = 3;
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

void Player::unhitableCountdown(){
	while(this->m_unhitable_seconds_left > 0){
		std::cerr << "unhitable seconds left: " << this->m_unhitable_seconds_left << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		this->m_unhitable_seconds_left--;
	}
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
				if(this->m_unhitable_seconds_left == 0){
					this->m_unhitable_seconds_left += 3;
					this->m_health--;
					if(this->m_health == 0){
						this->kill();
					}
					else{
						std::thread t(&Player::unhitableCountdown, this);
						t.detach();
					}
				}
			}
			break;
		}
		case EntityType::KEY: {
				this->m_key_count++;
				other->kill();
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
		case EntityType::HEALTH: {
			if(this->m_health < 3){
				this->m_health++;
				other->kill();
			}
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

int Player::health(){
	return this->m_health;
}
