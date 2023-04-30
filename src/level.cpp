#include "level.h"
#include "finish.h"
#include "ghost.h"
#include "key.h"
#include "wall.h"
#include "player.h"
#include "floor.h"
#include <QTextStream>
#include <fstream>
#include <iostream>

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
}

Entity* Level::createEntity(char c, int x, int y) {
  auto coords = this->translate(x, y);
  x = coords.first;
  y = coords.second;

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
      return (Entity*) new Floor(x, y);
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
		this->m_grid[y+1][x+1] = new Cell(createEntity(c, x+1, y), this);
    }
  }
  levelFile.close();
	
  for(int i = 0; i < m_bound_x + 2; i++) {
	  this->m_grid[0][i] = new Cell (createEntity('X', i, 0), this);
	  this->m_grid[m_bound_y + 1][i] = new Cell (createEntity('X', i, m_bound_y), this);
  }
  for(int i = 0; i < m_bound_y + 2; i++) {
	  this->m_grid[i][0] = new Cell(createEntity('X', 0, i), this);
	  this->m_grid[i][m_bound_x + 1] = new Cell(createEntity('X', m_bound_x, i), this);
  }
  this->dumpGrid();

  this->displayGrid();
}

void Level::displayGrid() {
  for(int row = 0; row < this->m_grid.size(); ++row) {
    for (int col = 0; col < this->m_grid[row].size(); ++col) {
      this->m_scene->addItem(this->m_grid[row][col]->getEntity());
      this->m_grid[row][col]->getEntity()->setSpriteScale(this->m_scale);
    }
  }
}

void Level::updateScene() {
  static int a=0;

  for(int row = 0; row < this->m_grid.size(); ++row) {
     for (int col = 0; col < this->m_grid[row].size(); ++col) {
       this->m_grid[row][col]->updateSprite(col, row);
     }
  }

  // for (auto entity : this->m_scene->items()) {
  //   ((Entity*) entity)->update();
  // }
}

int Level::scale() {
  return m_scale;
}

void Level::dumpGrid(){
	std::cerr << "Dumping grid" << this->m_grid.size() << " " <<this->m_grid[0].size() << std::endl;
	for(int i = 0; i < this->m_grid.size(); i++) {
		for(int j = 0; j < this->m_grid[i].size(); j++) {
			std::cerr << this->m_grid[i][j]->getEntity()->sprite_path << "\t";
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
