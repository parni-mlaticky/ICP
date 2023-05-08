/** 
 * @file ghost.h
 * @brief Header of the Ghost entity
 * @authors Ondřej Zobal
 * */


#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QObject>
#include <QKeyEvent>
#include <QPainter>
#include <iostream>
#include "entity.h"

/**
 * @class Ghost
 * @brief Class for the ghost entity
 */
class Ghost : public Entity {
// private members
private:
  /** 
   * @brief The remaining number of steps the ghost will move in the current direction 
   * */
  int m_steps_left;

// public methods
public:
  /**
   * @copydoc Entity::Entity(int x, int y, DrawableItem* item, int id)
   * */
  Ghost(int x, int y, DrawableItem* item, int id);
  /** 
   * @brief An update function for the entity, called every tick
   * */
  void update() override;

// private methods
private:
  /** 
   * @brief Chooses a new direction for the ghost
   * */
  void newDirection();

};
#endif
