#pragma once

#include "drawable.h"
#include "level.h"
#include "logger.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include "remote.h"
#include "scene.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <chrono>
#include <iostream>
#include <thread>
#include "logger.h"
#include <fstream>

class MainWindow : public QMainWindow {
  Q_OBJECT

// public members
public:
  /** Enum specifiying the game mode - play or replay */
  enum class GameMode {
      Play,
      Replay
  };

// public methods
public:
  /** 
   * @brief Initializes the main window 
   * */
  void initialize();
  /** 
   * @brief Constructor for the main window, used for singleplayer or replay
   * */
  explicit MainWindow(QString &levelFilePath,MainWindow::GameMode gameMode, QWidget *parent = nullptr);
  /** 
   * @brief Constructor for the main window, used for multiplayer
   * */
  explicit MainWindow(QString &levelFilePath, bool hosting, std::string host, int port, QWidget *parent=nullptr);
  /**
   * @brief Method called when a key is pressed
   * */
  void keyPressEvent(QKeyEvent *event) override;

  ~MainWindow() override;
  /** 
   * @brief loads the level into a string from a specified file path 
   * @param levelFilePath The path to the level file
   * @return The string representation of the level
   * */
  std::string loadLevelFile(QString levelFilePath);

// protected methods
protected:
  /** 
   * @brief Method called when the window is closed
   * */
  void closeEvent(QCloseEvent *event) override;

signals:
  /** 
   * @brief Signal emitted when the window is closed
   * */
  void windowClosed();
  void openMainMenu();
  void sendMessage(std::string);

// private members
private:
  /** 
   * @brief Method used to update the state of the displayed scene
   * Calls the methods which update the game logic in the background
   * */
  void update();
  /** 
   * @brief Scene used to display the game 
   * */
  Drawable *m_scene;
  /** 
   * @brief View used to display the game 
   * */
  QGraphicsView *m_view;

  /** 
   * @brief The level being played
   * */
  Level *m_level;
  /** 
   * @brief The logger used to log the game
   * */
  Log::Logger *m_logger;
  /** 
   * @brief The replay used to replay the game
   * */
  Log::Replay *m_replay;
  /** 
   * @brief True if the level has been loaded
   * */
  /** 
   * @brief The number of milliseconds between each game logic tick
   * */
  int m_log_tick_ms;
  /** 
   * @brief The number of milliseconds between each graphics tick
   * */
  int m_gfx_tick_ms; 


  int m_animation_frames; // TODO comment @Ondrej
  int m_frame_counter; // TODO comment @Ondrej
  /** 
   * @brief Specifies the game mode - play or replay
   * */
  MainWindow::GameMode gamemode;
  /** 
   * @brief Timer used to update the game logic
   * */
  QTimer *timer;
  /**
   * @brief Reference to the client is stored here when the game is played in multiplayer mode and this session acts as the client
   * */
  Remote* mp_client;
  /**
   * @brief Reference to the server is stored here when the game is played in multiplayer mode and this session acts as the server
   * */
  Remote* mp_server;

  bool m_replay_paused;
  public slots:
    void onRecive(std::string message);
    void on_connected_to_client();
    void on_connected_to_server();
};
