#include <QGraphicsEllipseItem>

class Key : public QGraphicsEllipseItem {
public:
  Key(qreal x, qreal y, qreal width, qreal height);

private:
  qreal x;
  qreal y;
  qreal width;
  qreal height;
};
