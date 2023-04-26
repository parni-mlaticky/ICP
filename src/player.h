#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QKeyEvent>
#include <QObject>

class Player : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  Player();

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void setDirection(int dx, int dy);

protected:
  void keyPressEvent(QKeyEvent *event) override;

public slots:
  void updatePosition();

private:
  int m_dx, m_dy;
  int m_speed;
};
#endif
