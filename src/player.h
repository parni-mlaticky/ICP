/** 
 * @file player.h
 * @brief Header for the Player entity
 * @authors Vladimír Hucovič, Ondřej Zobal, Petr Kolouch
 * */

#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include "entity.h"
#include <atomic>
#include "entity.h"
#include "wall.h"
#include "ghost.h"
#include "key.h"
#include "finish.h"
#include <iostream>
#include <thread>
#include <chrono>
/**
 * @class Player
 * @brief Class for the Player entity, controlled by the user
 */
class Player : public Entity {
	public:
		/**
		 * @brief Constructor for the player entity
		 * @param x the x coordinate of the player entity
		 * @param y the y coordinate of the player entity
		 * @param isLocal specifies if this is a local or remote player
		 * @param item the drawable item of the player
		 * @param id the unique id of this entity
		 */
		Player(int x, int y, bool isLocal, DrawableItem* item, int id);
		/** 
		 * @copydoc Entity::update()
		 * */
		void update() override;
		/** 
		 * @copydoc Entity::onCollision(Entity* other)
		 * */
		void onCollision(Entity* other) override;
		/** 
		 * @brief Checks if this player has reached the opened finish square 
		 * @return true if the player has reached the finish
		 * */
		bool reachedFinish();
		/** 
		 * @brief Gets the number of keys currently held by this player
		 * @return the number of keys held by this player
		 * */
		int keyCount();
		/** 
		 * @brief Gets the remaining health of this player
		 * @return the health of this player
		 * */
		int health();
		/** 
		 * @brief Handles key press events for the player
		 * @param event the key press event
		 * */
		void keyPressEvent(QKeyEvent *event) override;
		/**
		 * @brief Sets the move vector calculated by astar
		 * @param vector the move vector
		 * */
		void setMoveVector(std::vector<std::pair<int, int>> &vector);
		/** 
		 * @brief Sets the next cell this player will move to when autopathing
		 * */
		void autoSetDirection();
		/** 
		 * @brief Gets the next cell this player will move to when autopathing
		 * @return the next cell this player will move to
		 * */
		void clearMoveVector();
		/** 
		 * @brief Checks if there are moves left in the move vector
		 * */
		bool hasMoveVector();
		static std::pair<int, int> keypressToDirection(QKeyEvent* event);
		/**
		 * @brief Specifies if this player is local or remote
		 * */
		bool m_local_player;

	protected:
		// private members
	private:
		/**
		 * @brief Specifies if this player has reached the finish square
		 * */
		bool m_reached_finish = false;
		/** 
		 * @brief The number of ticks left on this player's boost powerup
		 * */
		std::atomic_int m_boost_ticks_left = 0;
		/** 
		 * @brief The number of keys held by this player
		 * */
		int m_key_count;
		/** 
		 * @brief The remaining health of this player
		 * */
		int m_health;
		/** 
		 * @brief The number of ticks left that this player cannot be hit by ghosts
		 * */
		std::atomic_int m_unhitable_ticks_left = 0;
		/** 
		 * @brief The vector containing the coordinates of the next cells this player will move to when the player is moving using the mouse
		 * */
		std::vector<std::pair<int, int>> moveVector;

};


#endif

