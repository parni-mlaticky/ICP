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

void Level::addEntity(char c, qreal x, qreal y) {
  Entity* entity = createEntity(c, x, y);
  if (entity != nullptr) {
    this->m_scene->addItem(entity);
  }
}

Level::Level(QGraphicsScene *scene, int window_w, int window_h) {
  this->m_scene = scene;
  this->m_scale = -1;
  this->m_window_w = window_w;
  this->m_window_h = window_h;
}

Entity* Level::createEntity(char c, qreal x, qreal y) {
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

  // Calculating maze offset to center maze.
  int base_x = 0 - bound_x/2;
  int base_y = 0 - bound_y/2;

  // Calculating scale
  int scale_x = m_window_w / (bound_x+2);
  int scale_y = m_window_h / (bound_y+2);
  this->m_scale = std::min(scale_x, scale_y);

  std::cerr << "scale: " << this->m_scale << std::endl;

  int x = base_x;
  int y = base_y;
  while (std::getline(levelFile, level)) {
    for (char c : level) {
      this->addEntity(c, x, y);
      // Make sure there is a floor under this entity.
      if (c != '.' || c != 'X') {
        this->addEntity('.', x, y);
      }
      x+=1;
    }
    x = base_x;
    y+=1;
  }
  levelFile.close();

  // Draw horizontal walls arround maze (including corenrs).
  for (int x = base_x-1; x < base_x + bound_x+1; x++) {
    this->addEntity('X', x, base_y-1);
    this->addEntity('X', x, base_y + bound_y);
  }

  // Draw vertical walls
  for (int y = base_y; y < base_y + bound_y; y++) {
    this->addEntity('X', base_x-1, y);
    this->addEntity('X', base_x + bound_x, y);
  }
}

void Level::updateScene() {
  for (auto entity : this->m_scene->items()) {
    ((Entity*) entity)->update();
  }
}

int Level::scale() {
  return m_scale;
}
