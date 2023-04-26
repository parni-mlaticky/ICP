#include <QGraphicsRectItem>

class Wall : public QGraphicsRectItem {
public:
  Wall(qreal x, qreal y, qreal width, qreal height);

private:
  qreal x;
  qreal y;
  qreal width;
  qreal height;
};
