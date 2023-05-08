/**
 * @file drawable.h
 * @brief Header for the drawable graphical interface
 * @authors Ondřej Zobal, Petr Kolouch
 * */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "drawable_item.h"
#include <string>

/**
 * @brief Way is which sprite can be rotated
 * */
enum class rotationType;

/**
 * @brief An interface/abstract class for sending drawing game elements on the screen
 * */
class Drawable {
	public:
		/**
		 * @brief Renders a freame on the screen
		 * @param frame_n Frame number (between 0 an frame_count)
		 * */
		virtual void render(int frame_n) = 0;
		/**
		 * @brief Draws a new item on the screen
		 * @param sprite_path Base name of the sprite
		 * @param frame_count How many frames does this drawable items's animation should have
		 * @param rType What kind of rotation mechanizm this should employ
		 * */
		virtual DrawableItem* drawItem(std::string sprite_path, int frame_count, rotationType rType) = 0;
		/**
		 * @brief Deletes an item from the screen
		 * @param item The item that will be delted
		 * */
		virtual void deleteItem(DrawableItem* item) = 0;
		/**
		 * @brief Tells dawaable how many rows and columns should appear on the screen
		 * @param x horizontal dimenstion
		 * @param y vertical dimenstion
		 * */
		virtual void setGridDimensions(int x, int y) = 0;
		/**
		 * @brief Places given tile everywhere as background
		 * @param sprite_path Sprite that should be tiles
		 * */
		virtual void drawBackgroundTiles(std::string sprite_path) = 0;
		/**
		 * @brief Translates pixel coordinates to grid coordinates
		 * @param x X coordinate
		 * @param y Y coordinate
		 * */
		virtual std::pair<int, int> reverseTranslate(int x, int y) = 0;
		/**
		 * @brief Sets the next interpolation target
		 * @param item Drawable item who's position is beeing set
		 * @param row The grid row to which should be interpolated
		 * @param col The grid column to which should be interpolated
		 * */
		virtual void moveTowards(DrawableItem* item, int row, int col) = 0;
		/**
		 * @brief Sets the position of a drawable item
		 * @param item Drawable item who's position is beeing set
		 * @param row Grid row which the item should be set to
		 * @param col Grid column which the item should be set to
		 * */
		virtual void setPosition(DrawableItem* item, int row, int col) = 0;
		/**
		 * @brief The number of key icons that should be displayed on the screen
		 * @param count Count of keys
		 * */
		virtual void setKeyCount(int count) = 0;
		/**
		 * @brief The number of health icons that should be displayed on the screen
		 * @param count Count of health
		 * */
		virtual void setHealthCount(int count) = 0;

		Drawable();
};

#endif // DRAWABLE_H_
