#include "level.h"
#include "finish.h"
#include "ghost.h"
#include "key.h"
#include "wall.h"
#include "player.h"
#include "floor.h"
#include <QTextStream>
#include <bits/types/cookie_io_functions_t.h>
#include <fstream>
#include <iostream>
#include <type_traits>

using namespace std;


void Level::addEntity(Entity* entity) {
  this->m_scene->addItem(entity);
}

Level::Level(QGraphicsScene *scene, int window_w, int window_h) {
  this->m_scene = scene;
  this->m_scale = -1;
  this->m_scale = -1;
  this->m_window_w = window_w;
  this->m_window_h = window_h;
  this->m_bound_x = -1;
  this->m_bound_y = -1;

  this->m_background_gfx = vector<Entity*>();
}

Entity* Level::createEntity(char c) {
  switch (c) {
    case 'T': {
      return (Entity*) new Finish();
    }
    case 'X': {
      return (Entity*) new Wall();
    }
    case 'G': {
      return (Entity*) new Ghost();
    }
    case 'K': {
      return (Entity*) new Key();
    }
    case 'S': {
      return (Entity*) new Player(true);
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
	for(int i = 0; i < m_bound_y + 2; i++) {
		this->m_grid[i].resize(m_bound_x + 2);
	}
	
	
  char c;
  for (int y = 0; y < m_bound_y; y++) {
    for (int x = 0; x < m_bound_x; x++) {
		levelFile >> c;
		this->m_grid[y+1][x+1] = createEntity(c);

    // Adding floor gfx under every cell. Floors are standalone
    // entities and are not part of the grid.
    this->addBackgroundFloor(x+1, y+1);
    }
  }
  levelFile.close();
	
  for(int i = 0; i < m_bound_x + 2; i++) {
	  this->m_grid[0][i] = createEntity('X');
	  this->m_grid[m_bound_y + 1][i] = createEntity('X');
  }
  for(int i = 0; i < m_bound_y + 2; i++) {
	  this->m_grid[i][0] = createEntity('X');
	  this->m_grid[i][m_bound_x + 1] = createEntity('X');
  }
  this->dumpGrid();

  this->displayGrid();
}

void Level::addBackgroundFloor(int x, int y) {
  std::cerr << "x " << x << " y "  << y << std::endl;
  Entity* floor = new Floor();
  this->m_background_gfx.push_back(floor);
  auto coords = this->translate(x, y);
  floor->setPos(coords.first, coords.second);
  floor->setSpriteScale(this->m_scale);
  this->m_scene->addItem(floor);
}

void Level::displayGrid() {
  for(int row = 0; row < this->m_grid.size(); ++row) {
    for (int col = 0; col < this->m_grid[row].size(); ++col) {
      this->m_scene->addItem(this->m_grid[row][col]);
    }
  }
}

void Level::updateScene() {
  for(int row = 0; row < this->m_grid.size(); ++row) {
    for (int col = 0; col < this->m_grid[row].size(); ++col) {
      if (this->m_grid[row][col] == nullptr) continue;
      this->m_grid[row][col]->setSpriteScale(this->m_scale);
      this->m_grid[row][col]->updateSprite(col, row, this);
    }
  }

  for (auto entity : this->m_scene->items()) {
    ((Entity*) entity)->update();
  }
}

int Level::scale() {
  return m_scale;
}

void Level::dumpGrid(){
	std::cerr << "Dumping grid" << this->m_grid.size() << " " <<this->m_grid[0].size() << std::endl;
	for(int i = 0; i < this->m_grid.size(); i++) {
		for(int j = 0; j < this->m_grid[i].size(); j++) {
      if (this->m_grid[i][j] == nullptr) {
        std::cerr << "space\t";
      }
      else {
        std::cerr << this->m_grid[i][j]->sprite_path << "\t";
      }
		}
		std::cerr << std::endl;
	}
}

std::pair<int, int> Level::translate(int x, int y) {
  // Calculating maze offset to center maze.
  int base_x = 0 - m_bound_x/2;
  int base_y = 0 - m_bound_y/2;

  // Calculating scale
  int scale_x = m_window_w / (m_bound_x+2);
  int scale_y = m_window_h / (m_bound_y+2);
  this->m_scale = std::min(scale_x, scale_y);

  x += base_x;
  x *= m_scale;

  y += base_y -1;
  y *= m_scale;

  this->m_scale = std::min(scale_x, scale_y);  auto result = std::pair<int, int>(x , y);

  return result;
}


void Level::updateGrid() {
	std::vector<std::vector<Entity*>> newGrid;
	newGrid.resize(m_bound_y + 2);
	for(int i = 0; i < m_bound_y + 2; i++) {
		newGrid[i].resize(m_bound_x + 2);
	}
	for(int row = 0; row < this->m_grid.size(); row++) {
		for(int col = 0; col < this->m_grid[row].size(); col++) {
			Entity* ent = this->m_grid[row][col];
      if (ent == nullptr) continue;
			pair<int, int> dxdy = ent->getDxDy();
			if(dxdy.first == 1){
				cerr << "Entity " << ent->sprite_path << " is moving right" << endl;
				if(!checkWall(row, col+1)){
					newGrid[row][col+1] = ent;
					newGrid[row][col] = new Floor();
				}
			}
			else if(dxdy.first == -1){
				if(!checkWall(row, col-1)){
					newGrid[row][col-1] = ent;
					newGrid[row][col] = new Floor();
				}
			}
			else{
				newGrid[row][col] = ent;
			}
		}
	}
	this->m_grid = newGrid;
}


bool Level::checkWall(int x, int y){
	cerr << "Checking wall at " << x << " " << y << endl;
	if(x >= this->m_grid.size() || x < 0) return true;
	if(y >= this->m_grid[x].size() || y < 0) return true;
	Entity* ent = this->m_grid[x][y];
	if(dynamic_cast<Wall*>(ent) != nullptr){
		return true;
	}
	return false;
}
