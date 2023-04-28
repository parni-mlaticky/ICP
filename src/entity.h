#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Entity : public QGraphicsPixmapItem {
public:
  Entity(qreal x, qreal y, qreal width, qreal height);

protected:
  qreal m_width;
  qreal m_height;
};
#endif
