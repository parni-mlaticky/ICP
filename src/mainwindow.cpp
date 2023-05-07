#include "mainwindow.h"

void MainWindow::initialize(){
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

	m_replay = nullptr; //new Log::Replay(loadLevelFile("replay/keysnatch.rpl"));
	m_logger = new Log::Logger();
    m_level = new Level((Drawable *)m_scene, this->m_logger, this->m_replay);
    this->m_scene->setHealthCount(3);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->start(this->m_gfx_tick_ms);
}

MainWindow::MainWindow(QString &levelContent, Client* client, Server* server, QWidget *parent) : QMainWindow(parent){
	this->initialize();
	std::string levelString = levelContent.toStdString();
	this->m_level->loadLevel(levelString);
	this->m_logger->logGrid(levelString);
	this->MPclient = client;
	this->MPserver = server;
}

MainWindow::MainWindow(QString &levelFilePath, MainWindow::GameMode gameMode, QWidget *parent)
    : QMainWindow(parent){

  this->initialize();
  if(gameMode == MainWindow::GameMode::Replay) {
      m_replay = new Log::Replay(loadLevelFile(levelFilePath));
  }
  std::string levelString = this->loadLevelFile(levelFilePath);
  m_level->loadLevel(levelString);
  m_logger->logGrid(levelString);


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

void MainWindow::closeEvent(QCloseEvent *event) {
    emit windowClosed();
    QMainWindow::closeEvent(event);
}

void MainWindow::update() {
  ++this->m_frame_counter;

  if (this->m_replay) {
    if (this->m_replay->isReplayFinished()) {
      disconnect(timer, &QTimer::timeout, this, &MainWindow::update);
      timer->stop();
      // TODO show menu from here
      std::cerr << "Finished replaying " << this->m_replay->getMaxTick() << " logical ticks."<< std::endl;
      this->close();
    }
  }

  if (this->m_frame_counter == this->m_animation_frames) {
    this->m_level->updateGrid();
    this->m_frame_counter = 0;
    if (this->m_replay) {
      this->m_replay->setNextTick();
    }
  }
  this->m_scene->render(m_frame_counter);

  // TODO save level on game over and show main menu.
  if (this->m_logger && this->m_level->isGameOver()) {
    // TODO Change filename to UTC timestamp.
    std::ofstream file("replay/game.rpl");
    file << m_logger->getFullLog();
    file.close();
    this->close();
  }
}

MainWindow::~MainWindow() = default;
