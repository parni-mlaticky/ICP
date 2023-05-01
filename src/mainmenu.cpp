#include "mainmenu.h"
#include "mainwindow.h"
#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);

  connect(ui.playButton, &QPushButton::clicked, this,
          &MainMenu::on_playButton_clicked);
  connect(ui.multiplayerButton, &QPushButton::clicked, this,
          &MainMenu::on_multiplayerButton_clicked);
  connect(ui.exitButton, &QPushButton::clicked, this,
          &MainMenu::on_exitButton_clicked);
  connect(ui.replayButton, &QPushButton::clicked, this,
          &MainMenu::on_replayButton_clicked);
}

MainMenu::~MainMenu() {
  if (mainWindow != nullptr) {
    delete mainWindow;
  }
}

void MainMenu::on_playButton_clicked() {
  if (mainWindow == nullptr) {
    mainWindow = new MainWindow(levelFile);
  }
  this->hide();
  mainWindow->show();
}

void MainMenu::on_multiplayerButton_clicked() {
  // Code to execute when the multiplayer button is clicked
}

void MainMenu::on_selectLevelButton_clicked() {
  QString levelFilePath =
      QFileDialog::getOpenFileName(this, tr("Select level"), LEVEL_FOLDER_PATH);

  if (!levelFilePath.isEmpty()) {
    levelFile = levelFilePath;
    emit(levelSelected(levelFilePath));
  }
};

void MainMenu::on_replayButton_clicked() {}

void MainMenu::on_exitButton_clicked() { this->close(); }
