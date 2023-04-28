#include "level.h"
#include "finish.h"
#include "ghost.h"
#include "key.h"
#include "wall.h"
#include "player.h"
#include <QTextStream>
#include <fstream>
#include <iostream>

void Level::addEntity(char c, qreal x, qreal y) {
  Entity* entity = createEntity(c, x, y);
  if (entity != nullptr) {
    entities.push_back(entity);
    this->m_scene->addItem(entity);
  }
}

Level::Level(QGraphicsScene *scene, int scale) {
  this->m_scene = scene;
  this->m_scale = scale;
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
  std::getline(levelFile, firstLine);
  std::cerr << firstLine << std::endl;

  entities = std::vector<Entity*>();

  int x = 0;
  int y = 0;

  while (std::getline(levelFile, level)) {
    for (char c : level) {
      this->addEntity(c, x, y);
      x+=1;
    }
    x = 0;
    y+=1;
  }
  levelFile.close();
}

void Level::updateScene() {
  for (auto entity : this->entities) {
    entity->update();
  }
}

int Level::scale() {
  return m_scale;
}
