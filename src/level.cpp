/** 
 * @file level.cpp
 * @brief Implementation of the Level class, which handles most of the game logic and manages the game state and entities
 * @authors Ondřej Zobal, Vladimír Hucovič, Petr Kolouch
 * */


#include "level.h"
#include "boost.h"
#include "entity.h"
#include "finish.h"
#include "ghost.h"
#include "key.h"
#include "player.h"
#include "wall.h"
#include "health.h"
#include <QTextStream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>
#include <thread>
#include "aStar.h"
#include <QGraphicsSceneMouseEvent>
#include "sprite.h"
using namespace std;


Level::Level(Drawable *drawable, Log::Logger* logger, Log::Replay* replay) : m_id(0) {
  this->m_drawable = drawable;
  this->m_bound_x = -1;
  this->m_bound_y = -1;
  this->m_logger = logger;
  this->m_replay = replay;
  srand(time(NULL));
}

void Level::addEntity(char c, int x, int y, int id, bool init) {
  DrawableItem *item;

  if (m_logger && !init) {
    m_logger->logCreation(m_id-1, c, x, y);
  }

  Entity* entity;
  switch (c) {
    case 'T': {
        item = m_drawable->drawItem("finish", 1, rotationType::ROTATE);
        entity = (Entity *)new Finish(x, y, item, id);
        break;
    }
    case 'X': {
        item = m_drawable->drawItem("wall", 1, rotationType::ROTATE);
        entity = (Entity *)new Wall(x, y, item, id);
        break;
    }
    case 'G': {
        item = m_drawable->drawItem("ghost", 1, rotationType::SPRITE_CHANGE);
        entity = (Entity *)new Ghost(x, y, item, id);
        break;
    }
    case 'K': {
        item = m_drawable->drawItem("key", 1, rotationType::ROTATE);
        entity = (Entity *)new Key(x, y, item, id);
        break;
    }
    case 'S': {
        item = m_drawable->drawItem("player", 6, rotationType::ROTATE);
        entity = (Entity *)new Player(x, y, true, item, id);
        break;
    }
    case '.': {
        return;
    }
    case 'B':{
        item = m_drawable->drawItem("boost", 1, rotationType::ROTATE);
        entity = (Entity*) new Boost(x, y, item, id);
        break;
    }
    case 'H':{
        item = m_drawable->drawItem("health", 1, rotationType::ROTATE);
        entity = (Entity*) new Health(x, y, item, id);
        break;
    }
    default: {
        std::cerr << "Invalid entity character used: " << c << std::endl;
        exit(1);
    }
  }

  m_grid[x][y].push_back(entity);
  this->m_entities[entity->m_type].push_back(entity);
  this->m_drawable->setPosition(entity->m_drawable_item, x, y);
}

void Level::loadLevel(const std::string &levelString) {
	std::istringstream levelStream(levelString);
	std::string firstLine;

	// Reading maze bounds;
	levelStream >> this->m_bound_x;
	levelStream >> this->m_bound_y;


	std::getline(levelStream, firstLine);


	this->m_drawable->setGridDimensions(m_bound_x + 1, m_bound_y + 1);
	this->m_drawable->drawBackgroundTiles("floor");

	cerr << "Loading level with bounds: " << m_bound_x << " " << m_bound_y << endl;

	this->m_grid.resize(m_bound_x + 2);
	for (int x = 0; x < m_bound_x + 2; x++) {
		this->m_grid[x].resize(m_bound_y + 2);
	}

	char c;
	for (int x = 0; x < m_bound_x; x++) {
		for (int y = 0; y < m_bound_y; y++) {
			levelStream >> c;
			if (c != '.') {
				cerr << "creating entity at " << x << " " << y << " with code " << c << endl;
				addEntity(c, x+1, y+1, m_id++, true);
			}
			else{
				//cerr << "creating empty space at " << x << " " << y << endl;
			}
		}
	}

	for(int i = 0; i < m_bound_x + 2; i++) {
		addEntity('X', i, 0, m_id++, true);
		addEntity('X', i, m_bound_y + 1, m_id++, true);
	}
	for(int i = 0; i < m_bound_y + 2; i++) {
		addEntity('X', 0, i, m_id++, true);
		addEntity('X', m_bound_x + 1, i, m_id++, true);
	}
	this->dumpGrid();
    this->m_drawable->setHealthCount(3);
}

void Level::spawnHealth(){
	int x, y;
	do{
		x = rand() % this->m_bound_x + 1;
		y = rand() % this->m_bound_y + 1;
		cerr << "trying to spawn health at " << x << " " << y << endl;
	}
	while(this->m_grid[x][y].size() != 0);
	addEntity('H', x, y, m_id++, false);
}

void Level::spawnBoost(){
	int x, y;
	do{
		x = rand() % this->m_bound_x + 1;
		y = rand() % this->m_bound_y + 1;
	}
	while(this->m_grid[x][y].size() != 0);
	addEntity('B', x, y, m_id++, false);
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
			if(type == PLAYER){
				entity->update();
			}
		}
		else {
			entity->update();
		}

		pair<int, int> dxdy = entity->getDxDy();
		int dx = dxdy.first;
		int dy = dxdy.second;
		std::pair<int, int> coords = entity->get_xy();
		this->m_drawable->setPosition(entity->m_drawable_item, coords.first, coords.second);
		if(!entity->canMove()) continue;
		entity->setAllowedDirections(this->checkDirections(coords.first, coords.second));
		if(m_logger){
			this->m_logger->logDirection(entity->getId(), entity->getDxDy().first, entity->getDxDy().second);
		}
		if(dx == 0 && dy == 0) continue;
		entity->m_drawable_item->setRotation(dx, dy);
		if(!checkWall(coords.first + dx, coords.second + dy)){
			entity->m_drawable_item->setAnimate(true);
			int newX = coords.first + dx;
			int newY = coords.second + dy;
			EntityVector* entitiesAtXY = &this->m_grid[coords.first][coords.second];
			auto it = std::find(entitiesAtXY->begin(), entitiesAtXY->end(), entity);
			if(it != entitiesAtXY->end()){
				entitiesAtXY->erase(it);
			}
			entity->set_xy(newX, newY);
			this->m_drawable->moveTowards(entity->m_drawable_item, newX, newY);
			this->m_grid[newX][newY].push_back(entity);
			entity->setAllowedDirections(this->checkDirections(newX, newY));
			this->triggerCollisions(entity);
		}
		else{
			entity->m_drawable_item->setAnimate(false);
			entity->stop();
		}
	}
}
void Level::removeDeadEntities(){
	for(auto entityTypeVecPair: this->m_entities){
		for(auto entity: entityTypeVecPair.second){
			if(!entity->isAlive()){
				this->m_logger->logRemoval(entity->getId(), entity->m_type, entity->get_xy().first, entity->get_xy().second);
				this->removeEntity(entity);
			}
		}
	}
}

void Level::triggerCollisions(Entity* ent){
	std::pair<int, int> coords = ent->get_xy();
	EntityVector collidingEntities = this->m_grid[coords.first][coords.second];
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
    if (stoi(command[1]) != ent->getId()) continue;

	if(!m_replay->playingBackwards()){
		ent->setDirection(stoi(command[2]), stoi(command[3]));
		std::cerr << "Setting direction to " << stoi(command[2]) << " " << stoi(command[3]) << std::endl;
	}
	else{
		ent->setDirection(-stoi(command[2]), -stoi(command[3]));
		std::cerr << "Setting direction to " << -stoi(command[2]) << " " << -stoi(command[3]) << std::endl;
	}
  }
}

void Level::tryToRemoveEntitiesFromReplay(bool backwards) {
    if (!backwards) return;
    for (auto command: this->m_replay->getLastTick()) {
        if (command[0] != "R") continue;
        int id = stoi(command[1]);
        char type = command[2][0];
        int x = stoi(command[3]);
        int y = stoi(command[4]);
		cerr << "Tryng to re-create entity " << type << " at " << x << " " << y <<endl;
        addEntity(type, x, y, id++, false);
        std::cerr << "briihh " << x << " x " << y << std::endl;
    }
}

void Level::tryToCreateEntitiesFromReplay(bool backwards) {
	if (backwards){
		for(auto command: this->m_replay->getLastTick()){
			if (command[0] != "C") continue;
			int id = stoi(command[1]);
			char type = command[2][0];
			int x = stoi(command[3]);
			int y = stoi(command[4]);
			auto entitiesAtXY = this->m_grid[x][y];
			for(auto entity: entitiesAtXY){
				if(entity->getId() == id){
					this->removeEntity(entity);
				}
			}
		}
		return;
	}
    for (auto command: this->m_replay->getLastTick()) {
        if (command[0] != "C") continue;
        int id = stoi(command[1]);
        char type = command[2][0];
        int x = stoi(command[3]);
        int y = stoi(command[4]);
        addEntity(type, x, y, id++, false);
        std::cerr << "briihh " << x << " x " << y << std::endl;
    }
}

void Level::updateGrid() {
    if (m_replay) {
        this->tryToCreateEntitiesFromReplay(m_replay->playingBackwards());
	}
	this->updateEntitiesOfType(EntityType::PLAYER);
	if(this->m_entities[EntityType::KEY].size() == 0){
		this->openFinishes();
	}
	else{
		this->closeFinishes();
	}
	this->checkPlayerWin();
	this->updateEntitiesOfType(EntityType::GHOST);
	this->updateEntitiesOfType(EntityType::KEY);
	this->updateEntitiesOfType(EntityType::FINISH);
	this->updateEntitiesOfType(EntityType::BOOST);
	this->updateEntitiesOfType(EntityType::HEALTH);
	this->removeDeadEntities();
	if(this->m_entities[EntityType::PLAYER].size() == 0){
		this->m_game_over = true;
	}
    if (!m_replay) {
        if(rand() % 100 < 98 && this->m_entities[EntityType::BOOST].size() == 0){
            cerr << "SPAWNING BOOST" << endl;
            this->spawnBoost();
        }
        if(rand() % 100 < 95 && this->m_entities[EntityType::HEALTH].size() == 0){
            cerr << "SPAWNING HEALTH" << endl;
            this->spawnHealth();
        }
    }
    if (m_replay) {
        this->tryToRemoveEntitiesFromReplay(m_replay->playingBackwards());
    }
	this->m_drawable->setHealthCount(((Player*) this->m_entities[EntityType::PLAYER][0])->health());
    this->m_drawable->setKeyCount(((Player *)this->m_entities[EntityType::PLAYER][0])->keyCount());
	this->dumpGrid();

	if(this->m_logger){
		this->m_logger->logTickEnd();
	}
}

bool Level::isGameOver(){
	return this->m_game_over;
}


void Level::closeFinishes(){
	EntityVector finishes = this->m_entities[EntityType::FINISH];
	for(Entity* f: finishes){
		((Finish*) f)->close();
	}
}

void Level::openFinishes(){
	EntityVector finishes = this->m_entities[EntityType::FINISH];
	for(Entity* f: finishes){
		((Finish*) f)->open();
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

void Level::keyPressEvent(QKeyEvent *event){
  if (m_replay) {
    return;
  }

  for(auto ent: this->m_entities[EntityType::PLAYER]){
	ent->keyPressEvent(event);
  }
}


EntityVector Level::findEntitiesAt(int x, int y){
	return this->m_grid[x][y];
}


void Level::mousePressEvent(QGraphicsSceneMouseEvent *event) {
		if(m_replay){ return; }
        if (event->button() == Qt::LeftButton) {
        qreal x = event->scenePos().x();
        qreal y = event->scenePos().y();
        auto test = this->m_drawable->reverseTranslate(x, y);
        std::cerr << "testing A star" << std::endl;
        Entity* playerEntity = this->m_entities[EntityType::PLAYER][0];
		((Player*)playerEntity)->clearMoveVector();
        std::pair<int, int>playerPos = playerEntity->get_xy();
        std::pair<int, int> start(playerPos.first, playerPos.second);
        std::pair<int, int> finish(this->m_drawable->reverseTranslate(x, y));

		cerr << "start: " << start.first << " " << start.second << endl;
		cerr << "finish: " << finish.first << " " << finish.second << endl;
        std::vector<std::pair<int, int>> path = Astar::calculatePath(start, finish, this->m_grid);
        ((Player*)playerEntity)->setMoveVector(path);
        std::cerr << "Path found:\n";
        for (const auto &coord : path) {
            std::cerr << '(' << coord.first << ", " << coord.second << ")\n";
        }
    }
}

