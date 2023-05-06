#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QKeyEvent>
#include <QObject>
#include "entity.h"
#include <atomic>

class Player : public Entity {
public:
  Player(int x, int y, bool isLocal, DrawableItem* item, int id);
  void update() override;
  void onCollision(Entity* other) override;
  bool reachedFinish();
  int keyCount();
  int health();
  void boostCountdown();
  void unhitableCountdown();
protected:
  void keyPressEvent(QKeyEvent *event) override;

public slots:

private:
  bool m_local_player;
  bool m_reached_finish = false;
  std::atomic_int m_boost_seconds_left = 0;
  int m_key_count;
  int m_health;
  std::atomic_int m_unhitable_seconds_left = 0;
};
#endif

