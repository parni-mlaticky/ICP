/** 
 * @file scene.cpp
 * @brief Implementation of the Scene class
 * @authors Ondřej Zobal, Petr Kolouch, Vladimír Hucovič
 * */

#include "scene.h"
#include "mainwindow.h"
#include <cmath>

Scene::Scene(int window_w, int window_h, int frames_between_updates, MainWindow* window) {
	this->m_window_w = window_w;
	this->m_window_h = window_h;
	this->m_update_grid = frames_between_updates;
	this->m_update_grid_counter = this->m_update_grid-1;
	this->m_window = window;
	this->keyCount = 0;
	this->healthCount = 0;
	this->healthOffset = 0;
	this->keyOffset = 0;

	this->setSceneRect(-100, -100, 200, 200);
	this->setFocus();

	QPixmapCache::setCacheLimit(200240);
}

void Scene::cacheSprites(const std::string dirPath) {
	QDir dir(dirPath.c_str());
	QStringList filters;
	filters << "*.png";
	QFileInfoList fileList = dir.entryInfoList(filters);

	for (const auto& fileInfo : fileList) {
		QPixmap pixmap(fileInfo.filePath());
		if (!pixmap.isNull()) {
			QString key = fileInfo.baseName();
			pixmap = pixmap.scaled(m_scale, m_scale, Qt::KeepAspectRatio);
			QPixmapCache::insert(key, pixmap);
		}
	}
}

void Scene::keyPressEvent(QKeyEvent* event) {
	m_window->keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
	m_window->mousePressEvent(event);
}

void Scene::render(int frame_n) {
	for (auto item : this->items()) {
		((Sprite*) item)->interpolate(frame_n, m_update_grid);
		if (frame_n % 5 == 0)
			((Sprite*) item)->animate();
	}
}

DrawableItem* Scene::drawItem(std::string sprite_path, int frame_count, rotationType rType) {
	Sprite* sprite = new Sprite(sprite_path, frame_count, rType);
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

	this->cacheSprites("./assets/");
}

void Scene::moveTowards(DrawableItem* item, int row, int col) {
	item->moveTowards(this->translate(row, col));
}

void Scene::setPosition(DrawableItem* item, int row, int col) {
	item->setPosition(this->translate(row, col));
}

void Scene::setKeyCount(int count) {
	if(count <= this->keyCount) return;
	qreal sceneWidth = this->sceneRect().width();
	qreal sceneHeight = this->sceneRect().height();
	this->keyCount = count;
	Sprite *key = new Sprite("key", 1, rotationType::ROTATE);
	key->setSpriteScale(this->m_scale);
	key->setPosition(std::pair<int, int>(-370 + this->keyOffset, -280));
	this->addItem(key);
	this->keySprites.push_back(key);
	this->keyOffset += 20;
}

void Scene::setHealthCount(int count) {
	if(count == this->healthCount) {
		return;
	}
	if (count < this->healthCount) {
		for(int i = 0; i < this->healthCount - count; i++){
			this->healthOffset -= 20;
			Sprite *deletedHealth = this->healthSprites.back();
			this->deleteItem(deletedHealth);
			this->healthSprites.pop_back();
		}
	} else {
		for (int i = 0; i < count - this->healthCount; i++) {
			Sprite *health = new Sprite("health", 1, rotationType::ROTATE);
			health->setSpriteScale(this->m_scale);
			health->setPosition(std::pair<int, int>(300 + this->healthOffset, -280));
			this->addItem(health);
			this->healthSprites.push_back(health);
			this->healthOffset += 20;
		}
	}
	this->healthCount = count;
}

void Scene::drawBackgroundTiles(std::string sprite_path) {
	for (int row = 0; row < this->m_x; row++) {
		for (int col = 0; col < this->m_y; col++) {
			Sprite* sprite = new Sprite(sprite_path, 1, rotationType::ROTATE);
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

std::pair<int, int> Scene::reverseTranslate(int x, int y) {
	double x_d = (double)x;
	double y_d = (double)y;
	int base_x = 0 - m_x / 2;
	int base_y = 0 - m_y / 2;

	x_d = floor(x_d / m_scale);
	x = x_d;
	x -= base_x - 1;

	y_d = floor(y_d / m_scale);
	y = y_d;
	y -= base_y - 1;

	auto result = std::pair<int, int>(y, x);

	return result;
}


