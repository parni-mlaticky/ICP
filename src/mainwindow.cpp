#include "mainwindow.h"
#include <QTimer>
#include <QVBoxLayout>
#include "server.h"
#include "client.h"
#include <chrono>
#include <thread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_scene(new QGraphicsScene(this)),
      m_view(new QGraphicsView(m_scene, this)) {

  const int height = 600;
  const int width = 800;

  setWindowTitle("Parni pacman");
  setFixedSize(width, height);
  setCentralWidget(m_view);
  m_view->setRenderHint(QPainter::Antialiasing);
  m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

  m_level = new Level(m_scene, width, height);
  m_scene->setSceneRect(-100, -100, 200, 200);
  m_level->loadLevel("./levels/level.txt");

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, m_level, &Level::updateScene);
  timer->start(1000 / 60);


  QTimer *timer2 = new QTimer(this);
  connect(timer2, &QTimer::timeout, m_level, &Level::updateGrid);
  timer2->start(400);
}

MainWindow::~MainWindow() = default;
