#pragma once

#include "drawable.h"
#include "level.h"
#include "logger.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include "client.h"
#include "server.h"
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  enum class GameMode {
      Play,
      Replay
  };
  // this constructor is used for singleplayer or replays
  explicit MainWindow(QString &levelFilePath,MainWindow::GameMode gameMode, QWidget *parent = nullptr);
  // this constructor is used for multiplayer
  explicit MainWindow(QString &levelContent, Client* client, Server* server, QWidget *parent = nullptr);
  void keyPressEvent(QKeyEvent *event);
  ~MainWindow() override;
  std::string loadLevelFile(QString levelFilePath);

protected:
  void closeEvent(QCloseEvent *event) override;

signals:
  void windowClosed();
  void openMainMenu();

private:
  void update();
  Drawable *m_scene;
  QGraphicsView *m_view;
  Level *m_level;
  Log::Logger *m_logger;
  Log::Replay *m_replay;
  bool m_levelLoaded;
  int m_log_tick_ms;
  int m_gfx_tick_ms;
  int m_animation_frames;
  int m_frame_counter;
  MainWindow::GameMode gamemode;
  QTimer *timer;
  // client or server stored here
  Client* MPclient;
  Server* MPserver;
  void initialize();
};
