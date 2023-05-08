/**
 * @file level.h
 * @brief Header for the Level class
 * @authors Ondřej Zobal, Vladimír Hucovič, Petr Kolouch
 * */

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


/** Vector of entities, used to represent entities on a grid cell */
using EntityVector = std::vector<Entity *>;
/** Vector of entity vectors, used to represent a row of a grid */
using Row = std::vector<EntityVector>;
/** Grid of entity vectors, used to represent the map in the level */
using Grid = std::vector<Row>;

/**
 * @class Level
 * @brief Class for the level, which contains most of the game logic
 */
class Level {
public:
   ~Level() {};
  /**
   * @brief Level constructor
   * @param drawable The drawable object of the level
   * @param logger The logger object of the level - used for logging the game
   * @param replay The replay object of the level - used to play back a recorded game
   * */
  Level(Drawable *drawable, Log::Logger *logger, Log::Replay *replay, bool is_multiplayer);
  /**
   * @brief Loads a level from a string
   * @param levelString The string representation of the level
   * */
  void loadLevel(const std::string &levelString);

  /**
   * @brief dumps the grid to standard error for debugging purposes (also enables playing the game in the terminal)
   * */
  void dumpGrid();

  /**
   * @brief Function used to update the state of the game every tick
   * */
  void updateGrid();
  /**
   * @brief checks if there is a wall at the given coordinate
   * @param x The x coordinate
   * @param y The y coordinate
   * */
  bool checkWall(int x, int y);
  /**
   * @brief sends the key press event to all entities
   * @param event The key press event
   * */
  void keyPressEvent(QKeyEvent *event);
  /**
   * @brief Triggers collisions for the given entity, with all entities in the same cell
   * @param ent The entity to trigger collisions for
   * */
  void triggerCollisions(Entity* ent);
  /**
   * @brief Removes the given entity from the grid
   * @param ent The entity to remove
   * */
  bool removeEntity(Entity *ent);
  /**
   * @brief Updates all entities of the given type
   * This enables some entities to be updated sooner than others - priority is always given to the player entities
   * @param type The type of the entities to update
   * */
  void updateEntitiesOfType(EntityType type);

  /**
   * @brief Returns the entities at the given coordinate
   * @param x The x coordinate
   * @param y The y coordinate
   * */
  EntityVector findEntitiesAt(int x, int y);
  /**
   * @brief Removes entities marked as dead from the grid
   * */
  void removeDeadEntities();
  /**
   * @brief Checks if the player has won the game
   * */
  void checkPlayerWin();
  /**
   * @brief Spawns a boost entity at a random location
   * */
  void spawnBoost();
  /**
   * @brief Spawns a health entity at a random location
   * */
  void spawnHealth();
  /**
   * @brief Checks if the game ended by the player getting eaten
   * @return True if the last player got eaten, false otherwise
   * */
  bool isGameOver();
   /**
   * @brief Returns direction of the local player in this instance
   * */
  std::pair<int, int> getLocalPlayerDirection();
  /**
   * @brief If the remote player is alive it will decode the given
   * command as directions and apply them to the remote player.
   * @param command Online protocol command for communication from
   * the cilent to the server.
   * */
  void setRemotePlayerDirection(std::string command);
	// TODO comment
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
// private methods
private:
  /**
   * @brief Checks for walls around the given coordinate and returns the directions that are not blocked by a wall
   * @param x The x coordinate
   * @param y The y coordinate
   * @return A vector of pairs of integers, representing the directions that are not blocked by a wall
   * */
  std::vector<std::pair<int, int>> checkDirections(int x, int y);
  /**
   * @brief Factory method for creating entities from the level string
   * @param c The character representing the type of the entity
   * @param x The x coordinate of the new entity
   * @param y The y coordinate of the new entity
   * @param id The id of the new entity
   * @param init True if the entity is being created at the start of the game, false otherwise
   * @return number of entities added.
   */
  int addEntity(char c, int x, int y, int id, bool init);
  /**
   * @brief If the game is being played from a replay, applies the directions from the replay to the given entity
   * @param ent The entity to apply the directions to
   * */
  void tryToApplyDirectionsFromReplay(Entity* ent);
  /**
   * @brief If the game is being played from a replay, tries to remove entities from the replay
   * @param backwards True if the replay is being played backwards, false otherwise
   * */
  void tryToRemoveEntitiesFromReplay(bool backwards);
  /**
   * @brief If the game is being played from a replay, tries to create entities from the replay
   * @param backwards True if the replay is being played backwards, false otherwise
   * */
  void tryToCreateEntitiesFromReplay(bool backwards);

  /**
   * @brief Opens all finishes (targets) in the level - called after all keys have been collected
   * */
  void openFinishes();

  /**
   * @brief Closes all finishes (targers) - used for backwards replay playback
   * */
  void closeFinishes();


// private members
private:
  /**
   * @brief The grid containing the Entity objects inside this level
   * */
  Grid m_grid;
  /**
   * @brief The logger object of the level - used for logging the game
   * */
  Log::Logger* m_logger;
  /**
   * @brief The replay object of the level - used to play back a recorded game
   * */
  Log::Replay* m_replay;

  /**
   * @brief Used to assign IDs to entities - keeps track of the last assigned ID
   * */
  int m_id;
  /**
   * @brief The number of rows in the level
   * */
  int m_bound_x;
  /**
   * @brief The number of columns in the level
   * */
  int m_bound_y;
  /**
   * @brief The drawable object of this level
   * */
  Drawable *m_drawable;
  /**
   * @brief True if the game is over
   * */
  bool m_game_over = false;
  /**
   * @brief True if the game runs as 2-player multiplater.
   * */
  bool m_is_multiplayer;
  /**
   * @brief Index of local player.
   * */
  int m_player_index;
  /**
   * @brief A map of entity types to vectors of entities of that type
   * Keeps track of entities of each type. This is used to update entities of each type separately, as well as
   * speeding up the process of looking up a specific entity, or an entity of a specific type
   * */
  std::unordered_map<EntityType, EntityVector> m_entities;
};

#endif
