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

  this->setSceneRect(-100, -100, 200, 200);
}

void Scene::render() {
  for (auto item : this->items()) {
    ((Sprite*) item)->interpolate(m_update_grid);
  }
}

DrawableItem* Scene::drawEntity(std::string sprite_path) {
  Sprite* sprite = new Sprite(sprite_path);
  sprite->setSpriteScale(m_scale);
  this->addItem(sprite);
  return sprite;
}

void Scene::deleteEntity(DrawableItem* item) {
  this->removeItem((Sprite*) item);
}

void Scene::setGridDimensions(int x, int y) {
  this->m_x = x;
  this->m_y = y;

  // Calculating scale
  int scale_x = m_window_w / (x + 2);
  int scale_y = m_window_h / (y + 2);
  this->m_scale = std::min(scale_x, scale_y);

  this->addBackgroundFloor(x, y);
}

void Scene::moveTowards(DrawableItem* item, int col, int row) {
  ((Sprite*) item)->moveTowards(this->translate(col, row));
}

void Scene::setPosition(DrawableItem* item, int col, int row) {
  ((Sprite*) item)->setPosition(this->translate(col, row));
}

void Scene::addBackgroundFloor(int x, int y) {
  std::cerr << "x " << x << " y " << y << std::endl;
  //TODO Entity *floor = new Floor();
  //this->m_background_gfx.push_back(floor);
  // auto coords = this->translate(x, y);
  // floor->setPos(coords.first, coords.second);
  // floor->setSpriteScale(this->m_scale);
  // this->m_scene->addItem(floor);
}

int Scene::scale() { return m_scale; }

std::pair<int, int> Scene::translate(int x, int y) {
  // Calculating maze offset to center maze.
  int base_x = 0 - m_x / 2;
  int base_y = 0 - m_y / 2;

  x += base_x;
  x *= m_scale;

  y += base_y - 1;
  y *= m_scale;

  auto result = std::pair<int, int>(x, y);

  return result;
}
