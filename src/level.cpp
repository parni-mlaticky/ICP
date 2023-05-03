#include "level.h"
#include "finish.h"
#include "ghost.h"
#include "key.h"
#include "player.h"
#include "wall.h"
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <algorithm>

using namespace std;

Level::Level(Drawable* drawable) {
  this->m_drawable = drawable;
  this->m_bound_x = -1;
  this->m_bound_y = -1;
  this->m_background_gfx = vector<Entity*>();
}

Entity* Level::createEntity(char c, int x, int y) {
  DrawableItem* item;
  switch (c) {
    case 'T': {
      item = m_drawable->drawItem("finish.png");
      return (Entity*) new Finish(x, y, item);
    }
    case 'X': {
      item = m_drawable->drawItem("wall.png");
      return (Entity*) new Wall(x, y, item);
    }
    case 'G': {
      item = m_drawable->drawItem("ghost.png");
      return (Entity*) new Ghost(x, y, item);
    }
    case 'K': {
      item = m_drawable->drawItem("key.png");
      return (Entity*) new Key(x, y, item);
    }
    case 'S': {
      item = m_drawable->drawItem("player.png");
      return (Entity*) new Player(x, y, true, item);
    }
    case '.': {
      return nullptr;
    }
    default: {
      throw "Invalid entity code!\n";
    }
  }
}

void Level::loadLevel(const QString &filename) {
  std::string level;
  std::string firstLine;
  std::ifstream levelFile(filename.toUtf8().constData());

  // Reading maze bounds;
  levelFile >> this->m_bound_x;
  levelFile >> this->m_bound_y;

  this->m_drawable->setGridDimensions(m_bound_x+1, m_bound_y+1);
  this->m_drawable->drawBackgroundTiles("floor.png");

  std::cerr << m_bound_x << ", " << m_bound_y << std::endl;
  std::getline(levelFile, firstLine);

  this->m_grid.resize(m_bound_y + 2);
  for (int i = 0; i < m_bound_y + 2; i++) {
    this->m_grid[i].resize(m_bound_x + 2);
  }

  char c;
  for (int y = 0; y < m_bound_y; y++) {
    for (int x = 0; x < m_bound_x; x++) {
      levelFile >> c;
      if(c != '.') {
        this->m_grid[y+1][x+1].push_back(createEntity(c, y+1, x+1));
      }
    }
  }
  levelFile.close();

  for(int i = 0; i < m_bound_x + 2; i++) {
	  this->m_grid[0][i].push_back(createEntity('X', 0, i));
	  this->m_grid[m_bound_y + 1][i].push_back(createEntity('X', m_bound_y + 1, i));
  }
  for(int i = 0; i < m_bound_y + 2; i++) {
	  this->m_grid[i][0].push_back(createEntity('X', i, 0));
	  this->m_grid[i][m_bound_x + 1].push_back(createEntity('X', i, m_bound_x + 1));
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
					std::cerr << this->m_grid[i][j][entIndex]->m_debug_char << ",";
				}
				std::cerr << "\t";
			}
		}
		std::cerr << std::endl;
	}
}


void Level::updateGrid() {
	Grid newGrid;
	newGrid.resize(m_bound_y + 2);
	for(int i = 0; i < m_bound_y + 2; i++) {
		newGrid[i].resize(m_bound_x + 2);
	}
	for(int row = 0; row < this->m_grid.size(); row++) {
		for(int col = 0; col < this->m_grid[row].size(); col++) {
			for(int entIndex = 0; entIndex < this->m_grid[row][col].size(); entIndex++){
				Entity* ent = this->m_grid[row][col][entIndex];
				if (ent == nullptr) continue;
				this->m_drawable->setPosition(ent->m_drawable_item, col, row);
				// entity cant move (wall, key, etc.) so skip it
				if(!ent->canMove()) {
					newGrid[row][col].push_back(ent);
					continue;
				}
				pair<int, int> dxdy = ent->getDxDy();
				int dx = dxdy.first;
				int dy = dxdy.second;
        if (ent->m_debug_char == 'G') {
          ((Ghost*) ent)->setAllowedDirections(checkDirections(row, col));
        }
        ent->update();
				if(dx == 0 && dy == 0){
					newGrid[row][col].push_back(ent);
					continue;
				}
				if(!checkWall(row+dy, col+dx)){
					newGrid[row+dy][col+dx].push_back(ent);
					ent->set_xy(row+dy, col+dx);
					this->m_drawable->moveTowards(ent->m_drawable_item, col+dx, row+dy);
				}
				else{
					ent->stop();
					newGrid[row][col].push_back(ent);
				}
			}
		}
	}
	this->m_grid = newGrid;
	this->dumpGrid();

	
	// find coordinates on which entities collided
	// TODO dont delete the graphical entities immediately, just mark them as deleted
	// and delete them after finishing the interpolation (or maybe halfway through?)
	std::vector<std::pair<int, int>> collisionsCoordsVector = this->getCollisionCoordinates();
	for(auto collisionCoords: collisionsCoordsVector){
		// for each colliding entity, call onCollision() with other entities on the same square
		vector<Entity*> entities = this->m_grid[collisionCoords.first][collisionCoords.second];
		for(Entity* ent: entities){
			for(Entity* ent2: entities){
				if(ent == ent2) continue;
				ent->onCollision(ent2);
			}
			// check if entity is still alive
			if(!ent->isAlive()){
				this->removeEntity(ent);
				this->m_drawable->deleteItem(ent->m_drawable_item);
				if(dynamic_cast<Player*>(ent) != nullptr){
					// YOU LOSE screen TODO
					// also this is probably not a good way to check if the player is dead
					cerr << "YOU LOSE" << endl;	
				}
			}
			// FIXME HACK
			auto keys = findEntities<Key>();
			cerr << "keys: " << keys.size() << endl;
			Player* p = dynamic_cast<Player*>(ent);
			if(p != nullptr){
				if(keys.size() == 0){
					this->openFinishes();
				}
				if(p->reachedFinish()){
					this->m_drawable->deleteItem(p->m_drawable_item);
					this->removeEntity(p);
					// YOU WIN screen i guess TODO
				}
			}
		}
	}
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
    out.push_back(std::pair<int, int>(0, -1));
  }
  if (!this->checkWall(x+1, y)) {
    out.push_back(std::pair<int, int>(0, 1));
  }
  if (!this->checkWall(x, y-1)) {
    out.push_back(std::pair<int, int>(-1, 0));
  }
  if (!this->checkWall(x, y+1)) {
    out.push_back(std::pair<int, int>(1, 0));
  }
  return out;
}

bool Level::checkWall(int x, int y){
	if(x >= this->m_grid.size() || x < 0) return true;
	if(y >= this->m_grid[x].size() || y < 0) return true;
	for(Entity* entity : this->m_grid[x][y]){
		if(dynamic_cast<Wall*>(entity) != nullptr){
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
			return true;
		}
	}
	return false;
}

std::vector<std::pair<int,int>> Level::getCollisionCoordinates(){
	std::vector<std::pair<int,int>> collisionCoordinates;
	for(int row = 0; row < this->m_grid.size(); ++row) {
		for (int col = 0; col < this->m_grid[row].size(); ++col) {
			if (this->m_grid[row][col].size() == 0) continue;
			if (this->m_grid[row][col].size() > 1) {
				collisionCoordinates.push_back(std::pair<int,int>(row, col));
			}
		}
	}
	return collisionCoordinates;
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

void Level::keyPressEvent(QKeyEvent* event) {
	for(int row = 0; row < this->m_grid.size(); row++) {
		for(int col = 0; col < this->m_grid[row].size(); col++) {
			for(int entIndex = 0; entIndex < this->m_grid[row][col].size(); entIndex++){
        this->m_grid[row][col][entIndex]->keyPressEvent(event);
      }
    }
  }
}
