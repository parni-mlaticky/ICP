/**
 * @file mainmenu.h
 * @brief Header for the MainMenu window class
 * @authors Petr Kolouch, Ondřej Zobal, Vladimír Hucovič 
 * */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "ui_mainmenu.h"
#include "multiplayerDialog.h"
#include <QWidget>
#include "mainwindow.h"
#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>
#include <iostream>
#include "multiplayerDialog.h"
class MainWindow;

class MainMenu : public QWidget {
  Q_OBJECT

public:
  /**
   * @brief Constructor for the main menu
   * @param parent The parent widget
   * */
  explicit MainMenu(QWidget *parent = nullptr);
  ~MainMenu();
  /**
   * @brief Gets the path to the selected level file
   * @return The path to the level file
   * */
  QString getLevelPath();

public slots:
	/**
	 * @brief Slot called when the main window is closed
	 * */
    void onMainWindowClosed();

private:
  /**
   * @brief The UI for the main menu
   * */
  Ui::Form ui;
  /**
   * @brief The game window
   * */
  MainWindow *mainWindow = nullptr;
  /**
   * @brief The path to the file containing the layout of the level
   * */
  QString levelFile = "./examples/levels/level.txt";
  /**
   * @brief The path to the file containing the replay of the level
   * */
  QString replayFile = "";
  /**
   * @brief The path to the folder containing the level layout files
   * */
  const QString LEVEL_FOLDER_PATH = "./examples/levels";
  /**
   * @brief The path to the folder containing the replay files
   * */
  const QString REPLAY_FOLDER_PATH = "./examples/replay";
  MultiplayerDialog* multiplayerDialog;

signals:
  /**
   * @brief Signal emitted when the play button is clicked
   * */
  void levelSelected(const QString &levelFilePath);

private slots:
  /**
   * @brief Slot called when the play button is clicked
   * */
  void on_playButton_clicked();
  /**
   * @brief Slot called when the multiplayer button is clicked
   * */
  void on_multiplayerButton_clicked();
  /**
   * @brief Slot called when the exit button is clicked
   * */
  void on_exitButton_clicked();
  /**
   * @brief Slot called when the replay button is clicked
   * */
  void on_replayButton_clicked();
  /**
   * @brief Slot called when the help button is clicked
   * */
  void on_helpButton_clicked();
  /**
   * @brief Slot called when the select level button is clicked
   * */
  void on_selectLevelButton_clicked();
  void on_mp_mode_selected(bool hosting, std::string host, int port);

private:
  const QString helpMessage = "<h2>Welcome to steam engine Pac-Man</h2>"
            "<p>Created by Ondřej Zobal, Vladimír Hucovič and Petr Kolouch for ICP class of 2023 at FIT VUT.</p>"
            "<p><h3>How to play:</h3></p>"
            "<p>You controll the Pac-Man using <i>W</i>, <i>A</i>, <i>S</i>, <i>D</i> or by cliking. Your goal is to collect all "
            "keys and head for the door. Make sure to avoid ghosts! If they touch you, you loose a life. "
            "You can replenish your health by colecting hearth which appear randomly on the map. You can get back "
            "at the ghosts by collecting a potion that enables you to eat the ghosts. Just like hearths, potions appear "
            "randomly on the map.</p>"
            "<p><h3>Menu options:</h3></p>"
            "<ul>"
            "<li><b>Play:</b></br> Start a new singleplayer game."
            "<li><b>Multiplayer:</b></br> Join a multiplayer game or create your own server to play with your friends.</li>"
            "<li><b>Select level:</b></br> Choose a map for your singleplayer or multiplayer game.</li>"
            "<li><b>Replay:</b></br> Watch replays of your past games. Use <i>SPACE</i> to pause and <i>A</i> to switch "
            "between playing forwards and backwards.</li>"
            "<li><b>Exit:</b></br> Quit the game</li>"
            "</ul>";
};

#endif
