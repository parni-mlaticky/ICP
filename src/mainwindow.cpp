#include "mainwindow.h"
#include "client.h"
#include "server.h"
#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <chrono>
#include <thread>

MainWindow::MainWindow(QString &levelFilePath, QWidget *parent)
    : QMainWindow(parent), m_scene(new QGraphicsScene(this)),
      m_view(new QGraphicsView(m_scene, this)), m_levelLoaded(false) {

  const int height = 600;
  const int width = 800;

  const int log_tick_ms = 200;
  const int gfx_tick_ms = 1000/60;

  setWindowTitle("Parni pacman");
  setFixedSize(width, height);
  setCentralWidget(m_view);
  m_view->setRenderHint(QPainter::Antialiasing);
  m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);


  int animation_frames = log_tick_ms/gfx_tick_ms;
  m_level = new Level(m_scene, width, height, animation_frames);
  m_level->loadLevel(levelFilePath);

  m_scene->setSceneRect(-100, -100, 200, 200);

  QTimer *timer = new QTimer(this);

  connect(timer, &QTimer::timeout, m_level, &Level::updateLevel);
  timer->start(gfx_tick_ms);
}

MainWindow::~MainWindow() = default;
