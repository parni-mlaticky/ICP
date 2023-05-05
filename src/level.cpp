#include "level.h"
#include "entity.h"
#include "finish.h"
#include "ghost.h"
#include "key.h"
#include "player.h"
#include "wall.h"
#include <QTextStream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

Level::Level(Drawable *drawable, Log::Logger* logger, Log::Replay* replay) : m_id(0) {
  this->m_drawable = drawable;
  this->m_bound_x = -1;
  this->m_bound_y = -1;
  this->m_background_gfx = vector<Entity *>();
  this->m_logger = logger;
  this->m_replay = replay;
}

Entity *Level::createEntity(char c, int x, int y) {
  DrawableItem *item;
  switch (c) {
  case 'T': {
    item = m_drawable->drawItem("finish.png");
    return (Entity *)new Finish(x, y, item, m_id++);
  }
  case 'X': {
    item = m_drawable->drawItem("wall.png");
    return (Entity *)new Wall(x, y, item, m_id++);
  }
  case 'G': {
    item = m_drawable->drawItem("ghost.png");
    return (Entity *)new Ghost(x, y, item, m_id++);
  }
  case 'K': {
    item = m_drawable->drawItem("key.png");
    return (Entity *)new Key(x, y, item, m_id++);
  }
  case 'S': {
    item = m_drawable->drawItem("player.png");
    return (Entity *)new Player(x, y, true, item, m_id++);
  }
  case '.': {
    return nullptr;
  }
  default: {
    throw "Invalid entity code!\n";
  }
  }
}

void Level::loadLevel(const std::string &levelString) {
	std::istringstream levelStream(levelString);
	std::string firstLine;

	// Reading maze bounds;
	levelStream >> this->m_bound_x;
	levelStream >> this->m_bound_y;

	this->m_drawable->setGridDimensions(m_bound_x + 1, m_bound_y + 1);
	this->m_drawable->drawBackgroundTiles("floor.png");

	std::cerr << m_bound_x << ", " << m_bound_y << std::endl;
	std::getline(levelStream, firstLine);


	this->m_drawable->setGridDimensions(m_bound_x+1, m_bound_y+1);
	this->m_drawable->drawBackgroundTiles("floor.png");

	std::cerr << m_bound_x << ", " << m_bound_y << std::endl;

	this->m_grid.resize(m_bound_x + 2);
	for (int x = 0; x < m_bound_x + 2; x++) {
		this->m_grid[x].resize(m_bound_y + 2);
	}

	char c;
	for (int x = 0; x < m_bound_y; x++) {
		for (int y = 0; y < m_bound_x; y++) {
			levelStream >> c;
			if (c != '.') {
				Entity* newEnt = createEntity(c, x+1, y+1);
				this->m_grid[x+1][y+1].push_back(newEnt);
				this->m_entities[newEnt->m_type].push_back(newEnt);
			}
		}
	}


	for(int i = 0; i < m_bound_x + 2; i++) {
		Entity* wall = createEntity('X', i, 0);
		auto wallXY = wall->get_xy();
		this->m_grid[wallXY.first][wallXY.second].push_back(wall);
		this->m_entities[wall->m_type].push_back(wall);
		wall = createEntity('X', i, m_bound_y + 1);
		wallXY = wall->get_xy();
		this->m_grid[wallXY.first][wallXY.second].push_back(wall);
		this->m_entities[wall->m_type].push_back(wall);
	}	
	for(int i = 0; i < m_bound_y + 2; i++) {
		Entity* wall = createEntity('X', 0, i);
		auto wallXY = wall->get_xy();
		this->m_grid[wallXY.first][wallXY.second].push_back(wall);
		this->m_entities[wall->m_type].push_back(wall);
		wall = createEntity('X', m_bound_x + 1, i);
		wallXY = wall->get_xy();
		this->m_grid[wallXY.first][wallXY.second].push_back(wall);
		this->m_entities[wall->m_type].push_back(wall);
	}
	for(int i = 0; i < m_bound_x + 2; i++) {
		for(int j = 0; j < m_bound_y + 2; j++) {
			for(auto ent : this->m_grid[i][j]) {
				auto coords = ent->get_xy();
				this->m_drawable->setPosition(ent->m_drawable_item, coords.first, coords.second);
			}
		}
	}
	this->dumpGrid();
}


void Level::dumpGrid(){
	std::cerr << "Dumping grid" << this->m_grid.size() << " " <<this->m_grid[0].size() << std::endl;
	for(int i = 0; i < this->m_grid.size(); i++) {
		for(int j = 0; j < this->m_grid[i].size(); j++) {
			if (this->m_grid[i][j].size() == 0) {
				std::cerr << ".\t";
			}
			else {
				for(int entIndex = 0; entIndex < this->m_grid[i][j].size(); entIndex++){
					std::cerr << (char) this->m_grid[i][j][entIndex]->m_type;
					if(entIndex != this->m_grid[i][j].size() - 1){
						std::cerr << ",";
					}
				}
				std::cerr << "\t";
			}
		}
		std::cerr << std::endl;
	}
}


void Level::updateEntitiesOfType(EntityType type){
	EntityVector entities = this->m_entities[type];
	for(Entity* entity : entities){
		this->triggerCollisions(entity);
    if (m_replay) {
      tryToApplyDirectionsFromReplay(entity);
    }
    else {
      entity->update();
    }

		cerr << entity->m_type << endl;
		pair<int, int> dxdy = entity->getDxDy();
		int dx = dxdy.first;
		int dy = dxdy.second;
		std::pair<int, int> coords = entity->get_xy();
		this->m_drawable->setPosition(entity->m_drawable_item, coords.first, coords.second);
		if(!entity->canMove()) continue;
		entity->setAllowedDirections(this->checkDirections(coords.first, coords.second));
		if(dx == 0 && dy == 0) continue;
		if(!checkWall(coords.first + dx, coords.second + dy)){
			EntityVector* entitiesAtXY = &this->m_grid[coords.first][coords.second];
			auto it = std::find(entitiesAtXY->begin(), entitiesAtXY->end(), entity);		
			cerr << coords.first << " " << coords.second << endl;
			if(it != entitiesAtXY->end()){
				entitiesAtXY->erase(it);
			}
			entity->set_xy(coords.first + dx, coords.second + dy);
			this->m_drawable->moveTowards(entity->m_drawable_item, coords.first + dx, coords.second + dy);
			this->m_grid[coords.first + dx][coords.second + dy].push_back(entity);
			entity->setAllowedDirections(this->checkDirections(coords.first + dx, coords.second + dy));
			this->triggerCollisions(entity);
		}
	}
}

void Level::removeDeadEntities(){
	for(auto entityTypeVecPair: this->m_entities){
		for(auto entity: entityTypeVecPair.second){
			if(!entity->isAlive()){
				this->removeEntity(entity);
			}
		}
	}
}


void Level::triggerCollisions(Entity* ent){
	std::pair<int, int> coords = ent->get_xy();
	EntityVector collidingEntities = this->findEntitiesAt(coords.first, coords.second);
	for(Entity* collidingEntity : collidingEntities){
		ent->onCollision(collidingEntity);
	}
}

void Level::checkPlayerWin(){
	for(Entity* playerEntity : this->m_entities[EntityType::PLAYER]){
		Player* player = dynamic_cast<Player*>(playerEntity);
		if(player->reachedFinish()){
			this->removeEntity(player);
		}
	}
}

void Level::tryToApplyDirectionsFromReplay(Entity* ent) {
  for (auto command : this->m_replay->getLastTick()) {
    if (command[0] != "D") continue;
    if (atoi(command[1].c_str()) != ent->getId()) continue;
    ent->setDirection(atoi(command[2].c_str()), atoi(command[3].c_str()));
  }
}

void Level::updateGrid() {
	this->updateEntitiesOfType(EntityType::PLAYER);
	if(this->m_entities[EntityType::KEY].size() == 0){
		this->openFinishes();
	}
	this->checkPlayerWin();
	this->updateEntitiesOfType(EntityType::GHOST);
	this->updateEntitiesOfType(EntityType::KEY);
	this->updateEntitiesOfType(EntityType::FINISH);
	this->removeDeadEntities();
	this->dumpGrid();
}


void Level::openFinishes(){
	auto finishes = findEntities<Finish>();
	for(auto finish: finishes){
		finish->open();
	}
}

std::vector<std::pair<int, int>> Level::checkDirections(int x, int y) {
  std::vector<std::pair<int, int>> out{};
  if (!this->checkWall(x-1, y)) {
    out.push_back(std::pair<int, int>(-1, 0));
  }
  if (!this->checkWall(x+1, y)) {
    out.push_back(std::pair<int, int>(1, 0));
  }
  if (!this->checkWall(x, y-1)) {
    out.push_back(std::pair<int, int>(0, -1));
  }
  if (!this->checkWall(x, y+1)) {
    out.push_back(std::pair<int, int>(0, 1));
  }
  return out;
}

bool Level::checkWall(int x, int y) {
  if (x >= this->m_grid.size() || x < 0)
    return true;
  if (y >= this->m_grid[x].size() || y < 0)
    return true;
  for (Entity *entity : this->m_grid[x][y]) {
    if (dynamic_cast<Wall *>(entity) != nullptr) {
      return true;
    }
  }
  return false;
}

bool Level::removeEntity(Entity* ent){
	std::pair<int, int> coords = ent->get_xy();
	for(int i = 0; i < this->m_grid[coords.first][coords.second].size(); i++){
		if(this->m_grid[coords.first][coords.second][i] == ent){
			this->m_grid[coords.first][coords.second].erase(this->m_grid[coords.first][coords.second].begin() + i);
			this->m_entities[ent->m_type].erase(std::find(this->m_entities[ent->m_type].begin(), this->m_entities[ent->m_type].end(), ent));
			this->m_drawable->deleteItem(ent->m_drawable_item); 
			return true;
		}
	}
	return false;
}

template<typename T>
std::vector<T*> Level::findEntities(){
	std::vector<T*> entities;
	for(int row = 0; row < this->m_grid.size(); row++) {
		for(int col = 0; col < this->m_grid[row].size(); col++) {
			for(int entIndex = 0; entIndex < this->m_grid[row][col].size(); entIndex++){
				Entity* entity = this->m_grid[row][col][entIndex];
				T* ent = dynamic_cast<T*>(entity);
				if(ent){
					entities.push_back(ent);
				}
			}
		}
	}
	return entities;
}

void Level::keyPressEvent(QKeyEvent *event) {
  if (m_replay) {
    return;
  }

  for (int row = 0; row < this->m_grid.size(); row++) {
    for (int col = 0; col < this->m_grid[row].size(); col++) {
      for (int entIndex = 0; entIndex < this->m_grid[row][col].size(); entIndex++) {
        this->m_grid[row][col][entIndex]->keyPressEvent(event);
      }
    }
  }
}


EntityVector Level::findEntitiesAt(int x, int y){
	return this->m_grid[x][y];
}
