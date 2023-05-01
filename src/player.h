#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QKeyEvent>
#include <QObject>
#include "level.h"

class Player : Entity {
public:
  Player(bool isLocal);
  void update() override;

protected:
  void keyPressEvent(QKeyEvent *event) override;

public slots:

private:
  bool m_local_player;
};
#endif
