#include <QGraphicsRectItem>

class Finish : public QGraphicsRectItem {
public:
  Finish(qreal x, qreal y, qreal width, qreal height);

private:
  qreal x;
  qreal y;
  qreal width;
  qreal height;
};
