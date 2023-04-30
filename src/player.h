#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QKeyEvent>
#include <QObject>
#include "level.h"

class Player : Entity {
public:
  Player(qreal x, qreal y, bool isLocal, Level* level);
  void update() override;

protected:
  void keyPressEvent(QKeyEvent *event) override;

public slots:
  void updatePosition();

private:
  bool m_local_player;
};
#endif
