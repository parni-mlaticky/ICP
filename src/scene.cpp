#include "scene.h"
#include "drawable_item.h"
#include "mainwindow.h"
#include <utility>
#include <iostream>

Scene::Scene(int window_w, int window_h, int frames_between_updates, MainWindow* window) {
  this->m_window_w = window_w;
  this->m_window_h = window_h;
  this->m_update_grid = frames_between_updates;
  this->m_update_grid_counter = this->m_update_grid-1;
  this->m_window = window;
  this->keyCount = 0;
  this->healthCount = 0;

  this->setSceneRect(-100, -100, 200, 200);
  this->setFocus();
}

void Scene::keyPressEvent(QKeyEvent* event) {
  m_window->keyPressEvent(event);
}

void Scene::render(int frame_n) {
  for (auto item : this->items()) {
    ((Sprite*) item)->interpolate(frame_n, m_update_grid);
  }
}

DrawableItem* Scene::drawItem(std::string sprite_path) {
  Sprite* sprite = new Sprite(sprite_path);
  sprite->setSpriteScale(m_scale);
  this->addItem(sprite);
  return sprite;
}

void Scene::deleteItem(DrawableItem* item) {
  this->removeItem((Sprite*) item);
}

void Scene::setGridDimensions(int x, int y) {
  this->m_x = x;
  this->m_y = y;

  // Calculating scale
  double scale_x = (double) m_window_w / (double)(x + 2);
  double scale_y = (double)m_window_h / (double)(y + 2);
  this->m_scale = std::min(scale_x, scale_y);
}

void Scene::moveTowards(DrawableItem* item, int row, int col) {
  item->moveTowards(this->translate(row, col));
}

void Scene::setPosition(DrawableItem* item, int row, int col) {
  item->setPosition(this->translate(row, col));
}

void Scene::setKeyCount(int count) {
  static int offset = 0;
  this->keyCount = count;
  Sprite *key = new Sprite("key.png");
  key->setSpriteScale(this->m_scale);
  key->setPosition(std::pair<int, int>(-350 + offset, -280));
  this->addItem(key);
  this->keySprites.push_back(key);
  offset += 20;
}

void Scene::setHealthCount(int count) {
  static int offset = 0;
  if (count < this->healthCount) {
    offset -= 10;
    Sprite *deletedHealth = this->healthSprites.back();
    this->deleteItem(deletedHealth);
    this->healthSprites.pop_back();
  } else {
    for (int i = 0; i < count; i++) {
      Sprite *health = new Sprite("health.png");
      health->setSpriteScale(this->m_scale);
      health->setPosition(std::pair<int, int>(300 + offset, -280));
      this->addItem(health);
      this->healthSprites.push_back(health);
      offset += 20;
    }
  }
}

void Scene::drawBackgroundTiles(std::string sprite_path) {
  for (int row = 0; row < this->m_x; row++) {
    for (int col = 0; col < this->m_y; col++) {
      Sprite* sprite = new Sprite(sprite_path);
      sprite->setPosition(this->translate(row, col));
      sprite->setSpriteScale(this->m_scale);
      sprite->setZ(-1);
      this->addItem(sprite);
    }
  }
}

int Scene::scale() { return m_scale; }

std::pair<int, int> Scene::translate(int x, int y) {
  // Calculating maze offset to center maze.
  int base_x = 0 - m_x / 2;
  int base_y = 0 - m_y / 2;

  x += base_x - 1;
  x *= m_scale;

  y += base_y - 1;
  y *= m_scale;

  auto result = std::pair<int, int>(y, x);

  return result;
}
