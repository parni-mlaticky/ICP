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


void Level::addEntity(char c, int x, int y) {
  Entity* entity = createEntity(c, x, y);
  std::cerr << "Adding entity: " << c << " at " << x << ", " << y << std::endl;
  if (entity != nullptr) {
	  this->m_grid[x][y] = new Cell(entity);
  }
}

Level::Level(QGraphicsScene *scene, int window_w, int window_h) {
  this->m_scene = scene;
  this->m_scale = -1;
  this->m_window_w = window_w;
  this->m_window_h = window_h;
}

Entity* Level::createEntity(char c, int x, int y) {
  switch (c) {
    case 'T': {
      return (Entity*) new Finish(x, y, this);
    }
    case 'X': {
      return (Entity*) new Wall(x, y, this);
    }
    case 'G': {
      return (Entity*) new Ghost(x, y, this);
    }
    case 'K': {
      return (Entity*) new Key(x, y, this);
    }
    case 'S': {
      return (Entity*) new Player(x, y, true, this);
    }
    case '.': {
      return (Entity*) new Floor(x, y, this);
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
  int bound_x;
  int bound_y;
  levelFile >> bound_x;
  levelFile >> bound_y;

  std::cerr << bound_x << ", " << bound_y << std::endl;
  std::getline(levelFile, firstLine);

	this->m_grid.resize(bound_y + 2);
	for(int i = 0; i < bound_y + 2; i++) {
		this->m_grid[i].resize(bound_x + 2);
	}
	
	
  char c;
  for (int y = 0; y < bound_y; y++) {
    for (int x = 0; x < bound_x; x++) {
		levelFile >> c;
		this->m_grid[y+1][x+1] = new Cell(createEntity(c, x+1, y+1));
    }
  }
  levelFile.close();
	
  for(int i = 0; i < bound_x + 2; i++) {
	  this->m_grid[0][i] = new Cell (createEntity('X', i, 0));
	  this->m_grid[bound_y + 1][i] = new Cell (createEntity('X', i, bound_y));
  }
  for(int i = 0; i < bound_y + 2; i++) {
	  this->m_grid[i][0] = new Cell(createEntity('X', 0, i));
	  this->m_grid[i][bound_x + 1] = new Cell(createEntity('X', bound_x, i));
  }
  this->dumpGrid();
}

void Level::updateScene() {
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
			std::cerr << this->m_grid[i][j]->getEntity()->sprite_path << "\t";
		}
		std::cerr << std::endl;
	}
}




