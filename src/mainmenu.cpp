/**
 * @file mainmenu.cpp
 * @brief Implementation of the MainMenu window class
 * @authors Petr Kolouch, Ondřej Zobal, Vladimír Hucovič
 * */

#include "mainmenu.h"
#include <QMessageBox>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
}

MainMenu::~MainMenu() {
  if (mainWindow != nullptr) {
    delete mainWindow;
    mainWindow = nullptr;
  }
}

void MainMenu::onMainWindowClosed() {
    if (mainWindow != nullptr) {
      delete mainWindow;
      mainWindow = nullptr;
    }
    this->show();
}

void MainMenu::on_playButton_clicked() {
    mainWindow = new MainWindow(levelFile, MainWindow::GameMode::Play);
    connect(mainWindow, SIGNAL(windowClosed()), this, SLOT(onMainWindowClosed()));
  this->hide();
  mainWindow->show();
}

void MainMenu::on_multiplayerButton_clicked() {
    this->multiplayerDialog = new MultiplayerDialog((QWidget*) this);
    this->hide();
    this->multiplayerDialog->exec();
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
        mainWindow = new MainWindow(replayFile, MainWindow::GameMode::Replay);
        connect(mainWindow, SIGNAL(windowClosed()), this, SLOT(onMainWindowClosed()));
        this->hide();
        mainWindow->show();
    }
}

void MainMenu::on_helpButton_clicked() {
    QMessageBox helpDialog(this);
    helpDialog.setWindowTitle("Help");
    helpDialog.setTextFormat(Qt::RichText);
    helpDialog.setText(this->helpMessage);
    helpDialog.exec();
}

void MainMenu::on_exitButton_clicked() { this->close(); }


QString MainMenu::getLevelPath() { return levelFile; }

void MainMenu::on_mp_mode_selected(bool hosting, std::string host, int port) {
  multiplayerDialog->close();
  if (mainWindow != nullptr) {
    delete mainWindow;
    mainWindow = nullptr;
  }
  mainWindow = new MainWindow(levelFile, hosting, host, port);
  connect(mainWindow, SIGNAL(windowClosed()), this, SLOT(onMainWindowClosed()));
  this->hide();
  mainWindow->show();
}
