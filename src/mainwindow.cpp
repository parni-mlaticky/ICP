#include "mainwindow.h"
#include "level.h"
#include <QTimer>
#include <QVBoxLayout>
#include "server.h"
#include "client.h"
#include <chrono>
#include <thread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_scene(new QGraphicsScene(this)),
      m_view(new QGraphicsView(m_scene, this)), m_player(new Player()) {

  setWindowTitle("Parni pacman");
  setFixedSize(800, 600);
  setCentralWidget(m_view);
  m_view->setRenderHint(QPainter::Antialiasing);
  m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

  Level level(m_scene);
  m_scene->setSceneRect(-100, -100, 200, 200);
  level.loadLevel("./levels/level.txt");
  m_scene->addItem(m_player);
  QPointF startingPos = level.getStartingPoint();
  m_player->setPos(startingPos.x(), startingPos.y());

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, m_player, &Player::updatePosition);
  timer->start(1000 / 60);
}

MainWindow::~MainWindow() = default;
