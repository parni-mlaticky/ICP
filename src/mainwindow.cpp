#include "mainwindow.h"
#include <qgraphicsitem.h>

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
  timer = new QTimer(this);

  this->mp_server = nullptr;
  this->mp_client = nullptr;
  this->m_level = nullptr;
  connect(timer, &QTimer::timeout, this, &MainWindow::update);
}

MainWindow::MainWindow(QString &levelFilePath, bool hosting, std::string host, int port, QWidget *parent) : QMainWindow(parent) {
	this->initialize();

  if (hosting) {
    this->mp_server = new Remote(this, port);
    std::string levelString = loadLevelFile(levelFilePath);
    this->m_logger->logGrid(levelString);
  }
  else {
    this->mp_client = new Remote(this, QString::fromStdString(host), port);
    this->m_replay = new Log::Replay("");
  }
}

MainWindow::MainWindow(QString &levelFilePath, MainWindow::GameMode gameMode, QWidget *parent)
    : QMainWindow(parent){

  this->initialize();
  if(gameMode == MainWindow::GameMode::Replay) {
    std::cerr << "AAA " << levelFilePath.toStdString();
      m_replay = new Log::Replay(loadLevelFile(levelFilePath));
  }

  m_level = new Level((Drawable *)m_scene, this->m_logger, this->m_replay);
  std::string levelString = this->loadLevelFile(levelFilePath);
  m_level->loadLevel(levelString);
  m_logger->logGrid(levelString);

  timer->start(this->m_gfx_tick_ms);
}

void MainWindow::on_connected_to_client() {
  std::cerr << "MainWindow: Client has connected to this server!" << std::endl;

  // emit sendMessage("Hello world z main window serveru!");
  // Poslat level
  emit sendMessage(this->m_logger->getGrid());
  // Zapnout clock
  m_level = new Level((Drawable *)m_scene, this->m_logger, nullptr);
  m_level->loadLevel(this->m_logger->getGrid());
  timer->start(this->m_gfx_tick_ms);
}

void MainWindow::on_connected_to_server() {
  std::cerr << "MainWindow: This client has connected to a server!" << std::endl;
  // emit sendMessage("Hello world z main window klienta!");
  // Přijmout level
  // std::cerr << this->mp_client->readUntill('\n');
  // Zapnout clock
}

void MainWindow::onRecive(std::string message) {
  std::cerr << "MainWindow: Recived new message: " << message << std::endl;
  if (mp_client) {
    this->m_replay->stream(message);
    // If the game wasn't started yet, but we already have
    // the map, start it!
    if (!m_level && this->m_replay->hasGrid()) {
      m_level = new Level((Drawable *)m_scene, this->m_logger, this->m_replay);
      m_logger->logGrid(this->m_replay->getGrid());
      m_level->loadLevel(this->m_replay->getGrid());
      timer->start(this->m_gfx_tick_ms);
    }
  }

  else if (mp_server) {
    // TODO
  }
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

void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent* event){
	std::cerr << "mouse press event" << std::endl;
	this->m_level->mousePressEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  // During MP windows can get this event even before the level is created.
  if (!m_level) {
    return;
  }

	// replay controls
	// TODO BIG HACK
	if(this->m_replay && !mp_client){
		if(event->key() == Qt::Key_Space){
			if(this->m_replay->isPaused()){
				this->timer->start();
			}
			if(this->m_replay){
				this->m_replay->togglePause();
			}
		}
		else if(event->key() == Qt::Key_D){
			if(this->m_replay->isPaused()){
				this->timer->start();
			}
		}
		else if(event->key() == Qt::Key_A){
			this->m_replay->setPreviousTick();
			this->m_replay->togglePlaybackDirection();
		}
	}
	// game controls
	this->m_level->keyPressEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    emit windowClosed();
    QMainWindow::closeEvent(event);
}

void MainWindow::update() {
  ++this->m_frame_counter;

  if (this->m_replay) {
    if (this->m_replay->isReplayFinished() && !mp_client) {
      disconnect(timer, &QTimer::timeout, this, &MainWindow::update);
      timer->stop();
      // TODO show menu from here
      std::cerr << "Finished replaying " << this->m_replay->getMaxTick() << " logical ticks."<< std::endl;
      this->close();
    }
  }

  if(this->m_replay && this->m_replay->isPaused()){
	  this->timer->stop();
  }

  if (this->m_frame_counter == this->m_animation_frames || (mp_client && this->m_replay->getTick() != this->m_replay->getMaxTick())) {
    // If the interpolation from the previous tick finished, but the new one
    // was not recived yet, nothing moves.
    if (this->mp_client && this->m_replay->getTick() == this->m_replay->getMaxTick()) {
        return;
    }

    this->m_level->updateGrid();
    if (mp_server) {
      emit sendMessage(this->m_logger->getLastTick());
    }
    this->m_frame_counter = 0;

    if (this->m_replay) {
      if(this->m_replay->playingBackwards()){
        this->m_replay->setPreviousTick();
      }
      else{
        this->m_replay->setNextTick();
      }
    }
  }
  this->m_scene->render(m_frame_counter);

  // TODO save level on game over and show main menu.
  if (this->m_logger && this->m_level->isGameOver()) {
    // TODO Change filename to UTC timestamp.
    std::ofstream file("replay/game.rpl");
    file << m_logger->getFullLog();
    file.close();
	this->timer->stop();
    this->close();
  }
}

void MainWindow::onDisconnect() {
  std::cerr << "Remote disconnected" << std::endl;
  if (this->timer) {
    this->timer->stop();
  }
  this->close();
}

MainWindow::~MainWindow() = default;
