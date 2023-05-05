#ifndef LEVEL_H_
#define LEVEL_H_

#include "drawable.h"
#include "entity.h"
#include "finish.h"
#include "ghost.h"
#include "key.h"
#include "player.h"
#include "logger.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <utility>
#include <vector>

using EntityVector = std::vector<Entity *>;
using EntityPair = std::pair<Entity *, Entity *>;
using Row = std::vector<EntityVector>;
using Grid = std::vector<Row>;

class Level {
public:
  Level(Drawable *drawable, Log::Logger *logger, Log::Replay *replay);
  void loadLevel(const std::string &levelString);
  void addEntity(Entity *entity);
  void updateScene();
  int scale();
  void dumpGrid();
  std::pair<int, int> translate(int x, int y);
  void updateGrid();
  bool checkWall(int x, int y);
  void keyPressEvent(QKeyEvent *event);
  void updatePlayers();
  void updateNonPlayers();
  void triggerCollisions(Entity* ent);
  // entities TODO maybe move this to private?
  std::unordered_map<EntityType, EntityVector> m_entities;
  std::vector<std::pair<int, int>> getCollisionCoordinates();
  void tryToApplyDirectionsFromReplay(Entity* ent);

  template <typename T> std::vector<T *> findEntities();

  bool removeEntity(Entity *ent);
  void updateLevel();

  void updateEntitiesOfType(EntityType type);
  EntityVector findEntitiesAt(int x, int y);

  void removeDeadEntities();
  void checkPlayerWin();

private:
  std::vector<std::pair<int, int>> checkDirections(int x, int y);
  Grid m_grid;
  EntityVector m_background_gfx;
  Entity *createEntity(char c, int x, int y);
  void displayGrid();
  void addBackgroundFloor(int x, int y);
  Log::Logger* m_logger;
  Log::Replay* m_replay;
  int m_id;
  int m_bound_x;
  int m_bound_y;
  Drawable *m_drawable;
  void openFinishes();
};

#endif
