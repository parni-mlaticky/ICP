/**
 * @file drawable_item.h
 * @brief Interface for drawable items
 * @authors Ondřej Zobal, Vladimír Hucovič, Petr Kolouch
 */
#ifndef DRAWABLE_ENTITY_H_
#define DRAWABLE_ENTITY_H_

#include <utility>
#include <string>

/**
  * @brief Handles sending messages
  * */
class DrawableItem {
public:
  /**
   * @brief Set interpolation target
   * @param coords coordinates to interpolate to
   * */
  virtual void moveTowards(std::pair<int, int> coords) = 0;
  /**
   * @brief Set position of this drawable_item
   * @param coords Coordinates to set position to
   * */
  virtual void setPosition(std::pair<int, int> coords) = 0;
  /**
   * @brief Set rotation of this drawable_item
   * @param dx Direction on X axis
   * @param dy Direction on Y axis
   * */
  virtual void setRotation(int dx, int dy) = 0;
  /**
   * @brief Enable or disable animation of thes drawable_item
   * @param allow If true, animations will be enabled, if falls they will disable
   * */
  virtual void setAnimate(bool allow) = 0;
  /**
   * @brief Changes sprite of this drawable item to given variant
   * @param variant The name of the variant
   * */
  virtual void setSpriteVariant(std::string variant) = 0;
  /**
   * @brief Changes sprite of this drawable item to the default variant
   * */
  virtual void setSpriteVariant() = 0;
  /**
   * @brief Sets the sprite Z value
   * @param z New z value
   * */
  virtual void setZ(int z) = 0;
  DrawableItem();
};

#endif // DRAWABLE_ENTITY_H_
