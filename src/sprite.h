/** 
 * @file sprite.h
 * @brief Implementation of sprites, which are the displayed images of entities in the game world
 * @authors Ondřej Zobal, Vladimír Hucovič
 * */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <utility>
#include "drawable_item.h"
#include <iostream>
#include <QPixmapCache>
#include <qnamespace.h>
#include <qpixmapcache.h>
class Scene;

// TODO Comment


/** 
 * @enum rotationType
 * @brief This enum is used to determine how the sprite should be rotated
 * SPRITE_CHANGE - The sprite is changed to a different one
 * ROTATE - The sprite is rotated
 * */
enum class rotationType {
	SPRITE_CHANGE,
	ROTATE
};


/** 
 * @class Sprite
 * @brief Objects of this class are used to display the entities in the game world
 * */
class Sprite : public QObject, public QGraphicsPixmapItem, public DrawableItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)

public:
  /** 
   * @brief Constructor for the Sprite class
   * @param sprite_path The path to the sprite image
   * @param frame_count The number of frames in the sprite image's animation
   * @param rType The rotation type of the sprite
   * */
  Sprite(std::string sprite_path, int frame_count, rotationType rType);
  /** 
   * @brief Sets the scale of the sprite depening on the size of the game window
   * @param scale The scale of the sprite
   * */
  void setSpriteScale(int scale);

  void interpolate(int frame_n, int frame_count);
  void setZ(int z);
  void animate();

  // Drawable Item
  void moveTowards(std::pair<int, int>) override;
  void setPosition(std::pair<int, int>) override;
  void setRotation(int dx, int dy) override;
  void setAnimate(bool allow) override;
  void setSpriteVariant(std::string variant) override;
  void setSpriteVariant() override;
protected:
  QPixmap m_pixmap;
  std::string m_sprite_path;
  std::string m_sprite_variant;
  int m_animation_frames;
  int m_current_animation_frame;
  rotationType rType;
  bool m_animate;
  int m_scale;
  std::pair<int, int> old_coords;
  std::pair<int, int> new_coords;
};

#endif // SPRITE_H_
