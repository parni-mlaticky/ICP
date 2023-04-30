#ifndef MAINMENU_H
#define MAINMENU_H

#include "ui_mainmenu.h"
#include <QWidget>

class MainMenu : public QWidget {
  Q_OBJECT

public:
  explicit MainMenu(QWidget *parent = nullptr);

private:
  Ui::Form ui;

private slots:
  void on_playButton_clicked();
  void on_multiplayerButton_clicked();
  void on_exitButton_clicked();
  void on_replayButton_clicked();
};

#endif

