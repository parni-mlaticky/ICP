#include "mainwindow.h"
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_scene(new QGraphicsScene(this)),
      m_view(new QGraphicsView(m_scene, this)) {

  setWindowTitle("Parni pacman");
  setFixedSize(800, 600);
  setCentralWidget(m_view);
  m_view->setRenderHint(QPainter::Antialiasing);
  m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

  m_level = new Level(m_scene, 32);
  m_scene->setSceneRect(-100, -100, 200, 200);
  m_level->loadLevel("./levels/level.txt");

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, m_level, &Level::updateScene);
  timer->start(1000 / 60);}

MainWindow::~MainWindow() = default;
