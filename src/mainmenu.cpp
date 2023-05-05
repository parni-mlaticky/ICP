#include "mainmenu.h"
#include "mainwindow.h"
#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>
#include <iostream>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);

  connect(ui.playButton, &QPushButton::clicked, this,
          &MainMenu::on_playButton_clicked);
  connect(ui.multiplayerButton, &QPushButton::clicked, this,
          &MainMenu::on_multiplayerButton_clicked);
  connect(ui.exitButton, &QPushButton::clicked, this,
          &MainMenu::on_exitButton_clicked);
}

MainMenu::~MainMenu() {
  if (mainWindow != nullptr) {
    delete mainWindow;
  }
}

void MainMenu::on_playButton_clicked() {
  if (mainWindow == nullptr) {
    mainWindow = new MainWindow(levelFile, MainWindow::GameMode::Play, this);
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
}

void MainMenu::on_replayButton_clicked() {
    QString replayFilePath = QFileDialog::getOpenFileName(this, tr("Select replay"), REPLAY_FOLDER_PATH);

    if (!replayFilePath.isEmpty()) {
        replayFile = replayFilePath;

        if (mainWindow == nullptr) {
            mainWindow = new MainWindow(replayFile, MainWindow::GameMode::Replay, this);
        }
        this->hide();
        mainWindow->show();
    }
}

void MainMenu::on_exitButton_clicked() { this->close(); }
