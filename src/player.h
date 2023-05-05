#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QKeyEvent>
#include <QObject>
#include "entity.h"

class Player : public Entity {
public:
  Player(int x, int y, bool isLocal, DrawableItem* item, int id);
  void update() override;
  void addKey();
  void onCollision(Entity* other) override;
  bool reachedFinish();
  int keyCount();

protected:
  void keyPressEvent(QKeyEvent *event) override;

public slots:

private:
  bool m_local_player;
  bool m_reached_finish = false;
  int m_key_count;
};
#endif

