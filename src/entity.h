/** 
 * @file entity.h
 * @brief Header for the entity class
 * @authors Vladimír Hucovič, Ondřej Zobal
 * */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <QKeyEvent>
#include "drawable_item.h"
#include <iostream>
#include <utility>
class Level;

/** 
 * @enum EntityType
 * @brief Specifies the type of an entity
 * */
enum EntityType{
  PLAYER = 'P',
  GHOST = 'G',
  KEY = 'K',
  FINISH = 'F',
  WALL = 'X',
  BOOST = 'B',
  HEALTH = 'H',
};

/** 
 * @class Entity
 * @brief Base class for all entities in the game
 * */
class Entity {

// public members
public:
   /** 
   * @brief The drawable item of the entity
   * */
  DrawableItem* m_drawable_item;
  /** 
   * @brief The type of the entity
   * */
  EntityType m_type;

// public methods
public:
  /** 
   * @brief Constructor for the entity
   * @param x The x coordinate of the entity
   * @param y The y coordinate of the entity
   * @param item The drawable item of the entity
   * @param id The unique id of this entity
   * */
  Entity(int x, int y, DrawableItem* item, int id);
  /** 
   * @brief An update function for the entity, called every tick
   * */
  virtual void update();
  /** 
   * @brief Sets the direction of the entity
   * @param dx The x direction of the entity
   * @param dy The y direction of the entity
   * */
  void setDirection(int dx, int dy);
  /**
   * @brief Gets the direction of the entity
   * @return A pair of ints, the x and y direction of the entity
   * */
  std::pair<int, int> getDxDy();
  /** 
   * @brief Stops the entity - sets its direction to 0, 0  
   * */
  void stop();
  /** 
   * @brief Gets the x and y coordinates of the entity // TODO rename
   * @return A pair of ints, the x and y coordinates of the entity
   * */
  std::pair<int, int> get_xy();
  /** 
   * @brief Sets the x and y coordinates of the entity // TODO rename
   * */
  void set_xy(int x, int y);
  /** 
   * @brief Defines what happens when to the entity when a key is pressed
   * @param event The key event
   * */
  virtual void keyPressEvent(QKeyEvent *event);
  /** 
   * @brief Defines the collision behaviour of the entity
   * @param other The entity that this entity collided with
   * */
  virtual void onCollision(Entity* other);
  /**
   * @brief Checks if this entity can move 
   * */
  bool canMove();
  /**
   * @brief Checks if the entity is alive
   */
  bool isAlive();
  /**
   * @brief Sets the alive property of the entity to false 
   */
  void kill();
  /**
   * Sets the allowed directions in which this entity can move in the next tick 
   */
  void setAllowedDirections(std::vector<std::pair<int, int>> directions);
  /**
   * @brief Gets the id of the entity
   */
  int getId();

// protected members
protected:
  /** 
   * @brief The ID of the entity
   * */
  int m_id;
  /** 
   * @brief The x coordinate of the entity inside the grid
   * */
  int m_x;
  /** 
   * @brief The y coordinate of the entity inside the grid
   * */
  int m_y;
  /** 
   * @brief The direction the entity is moving in on the x axis
   * */
  int m_dx;
  /** 
   * @brief The direction the entity is moving in on the y axis
   * */
  int m_dy;
  /** 
   * @brief Specifies if the entity is alive
   * */
  bool m_is_alive = true;
  /** 
   * @brief Specifies if the entity can move
   * */
  bool m_can_move = false;
  /** 
   * @brief Specifies the allowed directions in which the entity can move in the next tick
   * */
  std::vector<std::pair<int, int>> m_allowed_directions;
};

#endif
