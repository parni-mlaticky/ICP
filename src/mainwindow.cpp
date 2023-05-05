#include "mainwindow.h"
#include "client.h"
#include "scene.h"
#include "server.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <chrono>
#include <iostream>
#include <thread>
#include "logger.h"
#include <fstream>

MainWindow::MainWindow(QString &levelFilePath, QWidget *parent)
    : QMainWindow(parent), m_levelLoaded(false) {

  const int height = 600;
  const int width = 800;

  this->m_log_tick_ms = 200;
  this->m_gfx_tick_ms = 1000 / 60;

  this->m_animation_frames = m_log_tick_ms / m_gfx_tick_ms;
  this->m_frame_counter = m_animation_frames - 1;
  this->m_scene =
      new Scene(width, height, this->m_animation_frames, (MainWindow *)this);

  this->m_view = new QGraphicsView((Scene *)m_scene, this);
  setWindowTitle("Parni pacman");
  setFixedSize(width, height);
  setCentralWidget(m_view);
  m_view->setRenderHint(QPainter::Antialiasing);
  m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

  m_level = new Level((Drawable *)m_scene, nullptr, nullptr);
  std::string levelString = this->loadLevelFile(levelFilePath);
  m_level->loadLevel(levelString);

  QTimer *timer = new QTimer(this);

  connect(timer, &QTimer::timeout, this, &MainWindow::update);
  timer->start(this->m_gfx_tick_ms);
}

std::string MainWindow::loadLevelFile(QString levelFilePath) {
  QFile file(levelFilePath);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    std::cerr << "Failed to open the file containing level" << std::endl;
    exit(1);
  }
  QTextStream in(&file);
  QString level = in.readAll();
  file.close();

  return level.toStdString();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  this->m_level->keyPressEvent(event);
}

void MainWindow::update() {
  ++this->m_frame_counter;

  if (this->m_frame_counter == this->m_animation_frames) {
    m_level->updateGrid();
    this->m_frame_counter = 0;
  }
  this->m_scene->render(m_frame_counter);
}

MainWindow::~MainWindow() = default;
