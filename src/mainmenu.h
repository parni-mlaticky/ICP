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
  QString levelFile = "./levels/level.txt";
  /**
   * @brief The path to the file containing the replay of the level
   * */
  QString replayFile = "";
  /**
   * @brief The path to the folder containing the level layout files
   * */
  const QString LEVEL_FOLDER_PATH = "./levels";
  /**
   * @brief The path to the folder containing the replay files
   * */
  const QString REPLAY_FOLDER_PATH = "./replay";
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
  const QString helpMessage = "<h2>Welcome to steam engine pacman</h2>"
            "<p><b>Menu options:</b></p>"
            "<ul>"
            "<li>Play (singleplayer): Start a new singleplayer game"
            "your goal is to collect keys to open the finish, avoid enemy impostors or eat them within 5 seconds after colleting a boost.</li>"
            "<li>Multiplayer: Join a multiplayer game or create your own server to play with your friends</li>"
            "<li>Select level: Choose a level map for your singleplayer or multiplayer gameplay</li>"
            "<li>Replay: Watch a replay of your last game in an autoplay mode or use your keys to pause, forward or backward the replay</li>"
            "<li>Exit: Exit the game</li>";
};

#endif
