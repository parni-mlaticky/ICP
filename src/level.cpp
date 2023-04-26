#include "level.h"
#include "finish.h"
#include "ghost.h"
#include "key.h"
#include "wall.h"
#include <QTextStream>
#include <fstream>
#include <iostream>

Level::Level(QGraphicsScene *scene) { this->m_scene = scene; }
void Level::loadLevel(const QString &filename) {
  int x = 0;
  int y = 0;
  std::string level;
  std::string firstLine;
  std::ifstream levelFile(filename.toUtf8().constData());
  std::getline(levelFile, firstLine);
  std::cerr << firstLine << std::endl;
  while (std::getline(levelFile, level)) {
    for (char c : level) {
      switch (c) {
      case '.': {
        break;
      }
      case 'T': {
        Finish finish(x, y, 1, 1);
        break;
      }
      case 'X': {
        Wall wall(x, y, 1, 1);
        break;
      }
      case 'G': {
        Ghost ghost(x, y, 1, 1);
        break;
      }
      case 'K': {
        Key key(x, y, 1, 1);
        break;
      }
      case 'S': {
        QPointF start(x, y);
        this->m_startingPoint = start;
        break;
      }
      }
      x++;
    }
    y++;
  }
  levelFile.close();
}
void Level::addEntity(char entityType, int gridX, int gridY) {
  qreal x = gridX * GRID_SIZE;
  qreal y = gridY * GRID_SIZE;
}

QPointF Level::getStartingPoint() {
  return this->m_startingPoint;
  // QPointF debugPos(0, 0);
  // return debugPos;
}

QPointF Level::getFinishPoint() { return this->m_finishPoint; }
