#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);

  connect(ui.playButton, &QPushButton::clicked, this, &MainMenu::on_playButton_clicked);
  connect(ui.multiplayerButton, &QPushButton::clicked, this, &MainMenu::on_multiplayerButton_clicked);
  connect(ui.exitButton, &QPushButton::clicked, this, &MainMenu::on_exitButton_clicked);
  connect(ui.replayButton, &QPushButton::clicked, this, &MainMenu::on_replayButton_clicked);
}

void MainMenu::on_playButton_clicked() {
  // Code to execute when the play button is clicked
}

void MainMenu::on_multiplayerButton_clicked() {
  // Code to execute when the multiplayer button is clicked
}

void MainMenu::on_replayButton_clicked() {

}

void MainMenu::on_exitButton_clicked() {
  this->close();
}

