#ifndef MAINMENU_H
#define MAINMENU_H

#include "ui_mainmenu.h"
#include <QWidget>

class MainWindow;

class MainMenu : public QWidget {
  Q_OBJECT

public:
  explicit MainMenu(QWidget *parent = nullptr);
  ~MainMenu();


private:
  Ui::Form ui;
  MainWindow *mainWindow = nullptr;
  QString levelFile = "./levels/level.txt";
  QString replayFile = "";
  const QString LEVEL_FOLDER_PATH = "./levels";
  const QString REPLAY_FOLDER_PATH = "./replay";

signals:
  void levelSelected(const QString &levelFilePath);

private slots:
  void on_playButton_clicked();
  void on_multiplayerButton_clicked();
  void on_exitButton_clicked();
  void on_replayButton_clicked();
  void on_selectLevelButton_clicked();
};

#endif
