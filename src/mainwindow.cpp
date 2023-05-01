#include "mainwindow.h"
#include "client.h"
#include "server.h"
#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <chrono>
#include <thread>
#include <QKeyEvent>
#include "scene.h"

MainWindow::MainWindow(QString &levelFilePath, QWidget *parent)
    : QMainWindow(parent), m_levelLoaded(false) {

  const int height = 600;
  const int width = 800;

  const int log_tick_ms = 200;
  const int gfx_tick_ms = 1000/60;

  int animation_frames = log_tick_ms/gfx_tick_ms;
  auto scene = new Scene(width, height, animation_frames, (MainWindow*) this);

  this->m_view = new QGraphicsView(scene, this);
  setWindowTitle("Parni pacman");
  setFixedSize(width, height);
  setCentralWidget(m_view);
  m_view->setRenderHint(QPainter::Antialiasing);
  m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

  m_level = new Level((Drawable*) scene);
  m_level->loadLevel(levelFilePath);

  QTimer *timer = new QTimer(this);

  //connect(timer, &QTimer::timeout, m_level, &Level::updateLevel);
  timer->start(gfx_tick_ms);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  this->m_level->keyPressEvent(event);
}

MainWindow::~MainWindow() = default;
