#include "level.h"
#include "finish.h"
#include "floor.h"
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

void Level::addEntity(Entity *entity) { this->m_scene->addItem(entity); }

Level::Level(QGraphicsScene *scene, int window_w, int window_h, int update_grid) {
  this->m_scene = scene;
  this->m_scale = -1;
  this->m_scale = -1;
  this->m_window_w = window_w;
  this->m_window_h = window_h;
  this->m_bound_x = -1;
  this->m_bound_y = -1;
  this->m_background_gfx = vector<Entity *>();
  this->m_background_gfx = vector<Entity*>();
  this->m_update_grid = update_grid;
  this->m_update_grid_counter = update_grid-1;
}

Entity* Level::createEntity(char c, int x, int y) {
  switch (c) {
    case 'T': {
      return (Entity*) new Finish(x, y);
    }
    case 'X': {
      return (Entity*) new Wall(x, y);
    }
    case 'G': {
      return (Entity*) new Ghost(x, y);
    }
    case 'K': {
      return (Entity*) new Key(x, y);
    }
    case 'S': {
      return (Entity*) new Player(x, y, true);
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

      // Adding floor gfx under every cell. Floors are standalone
      // entities and are not part of the grid.
      this->addBackgroundFloor(x + 1, y + 1);
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

  this->displayGrid();
}

void Level::addBackgroundFloor(int x, int y) {
  std::cerr << "x " << x << " y " << y << std::endl;
  Entity *floor = new Floor();
  this->m_background_gfx.push_back(floor);
  auto coords = this->translate(x, y);
  floor->setPos(coords.first, coords.second);
  floor->setSpriteScale(this->m_scale);
  this->m_scene->addItem(floor);
}

void Level::displayGrid() {
  for (int row = 0; row < this->m_grid.size(); ++row) {
    for (int col = 0; col < this->m_grid[row].size(); ++col) {
		for(int entIndex = 0; entIndex < this->m_grid[row][col].size(); entIndex++){
			this->m_scene->addItem(this->m_grid[row][col][entIndex]);
		}
    }
  }
}

void Level::updateScene() {
  for (int row = 0; row < this->m_grid.size(); ++row) {
    for (int col = 0; col < this->m_grid[row].size(); ++col) {
      if (this->m_grid[row][col].size() == 0) continue;
      for(int entIndex = 0; entIndex < this->m_grid[row][col].size(); entIndex++){
        this->m_grid[row][col][entIndex]->setSpriteScale(this->m_scale);
        this->m_grid[row][col][entIndex]->interpolate(this->m_update_grid);
      }
    }
  }

  for (auto entity : this->m_scene->items()) {
    ((Entity *)entity)->update();
  }
}

int Level::scale() { return m_scale; }

void Level::dumpGrid(){
	std::cerr << "Dumping grid" << this->m_grid.size() << " " <<this->m_grid[0].size() << std::endl;
	for(int i = 0; i < this->m_grid.size(); i++) {
		for(int j = 0; j < this->m_grid[i].size(); j++) {
			if (this->m_grid[i][j].size() == 0) {
				std::cerr << ".\t";
			}
			else {
				for(int entIndex = 0; entIndex < this->m_grid[i][j].size(); entIndex++){
					std::cerr << this->m_grid[i][j][entIndex]->sprite_path[0] << ",";
				}
				std::cerr << "\t";
			}
		}
		std::cerr << std::endl;
	}
}

std::pair<int, int> Level::translate(int x, int y) {
  // Calculating maze offset to center maze.
  int base_x = 0 - m_bound_x / 2;
  int base_y = 0 - m_bound_y / 2;

  // Calculating scale
  int scale_x = m_window_w / (m_bound_x + 2);
  int scale_y = m_window_h / (m_bound_y + 2);
  this->m_scale = std::min(scale_x, scale_y);

  x += base_x;
  x *= m_scale;

  y += base_y - 1;
  y *= m_scale;

  this->m_scale = std::min(scale_x, scale_y);
  auto result = std::pair<int, int>(x, y);

  return result;
}

void Level::updateGrid() {
	cerr << "Updating grid" << endl;
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
        ent->updateSprite(col, row, this);
				pair<int, int> dxdy = ent->getDxDy();
				int dx = dxdy.first;
				int dy = dxdy.second;
				if(dx == 0 && dy == 0){
					newGrid[row][col].push_back(ent);
					continue;
				}

				if(!checkWall(row+dy, col+dx)){
					newGrid[row+dy][col+dx].push_back(ent);
					ent->set_xy(row+dy, col+dx);
          ent->move_to(col+dx, row+dy, this);
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

	/* TODO add bool or something to indicate that player has picked up a key */
	std::pair<Player*, Key*> playerKeyPair = this->checkPlayerKeyPickup();
	if(playerKeyPair.first != nullptr){
		removeEntity(playerKeyPair.second);
		this->m_scene->removeItem(playerKeyPair.second);
	}
}

void Level::updateLevel() {
  ++this->m_update_grid_counter;
  // Execute grid update once in m_update_grid frames.
  if (this->m_update_grid_counter == this->m_update_grid) {
    this->m_update_grid_counter = 0;
    // Updates logical grid.
    this->updateGrid();
  }

  // Updates sprites
  this->updateScene();
}

bool Level::checkWall(int x, int y){
	cerr << "Checking wall at " << x << " " << y << endl;
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
	for(int row = 0; row < this->m_grid.size(); ++row) {
		for (int col = 0; col < this->m_grid[row].size(); ++col) {
			if (this->m_grid[row][col].size() == 0) continue;
			for(int entIndex = 0; entIndex < this->m_grid[row][col].size(); entIndex++){
				if(this->m_grid[row][col][entIndex] == ent){
					this->m_grid[row][col].erase(this->m_grid[row][col].begin() + entIndex);
					return true;
				}
			}
		}
	}
	return false;
}


std::pair<Player*, Key*> Level::checkPlayerKeyPickup(){
	auto players = this->findEntities<Player>();
	auto keys = this->findEntities<Key>();
	for(Player* p: players){
		for(Key* k: keys){
			if(p->get_xy() == k->get_xy()){
				return std::pair<Player*, Key*>(p, k); 
			}
		}
	}
	return std::pair<Player*, Key*>(nullptr, nullptr);
}

template<typename T>
T* Level::findEntityAt(int x, int y){
	for(Entity* entity : this->m_grid[x][y]){
		T* ent = dynamic_cast<T*>(entity);
		if(ent){
			return dynamic_cast<T*>(entity);
		}
		else{
			return nullptr;
		}
	}
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
