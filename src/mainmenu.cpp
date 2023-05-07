#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);

  connect(ui.playButton, &QPushButton::clicked, this,
          &MainMenu::on_playButton_clicked);
  connect(ui.exitButton, &QPushButton::clicked, this,
          &MainMenu::on_exitButton_clicked);
}

MainMenu::~MainMenu() {
  if (mainWindow != nullptr) {
    delete mainWindow;
  }
}

void MainMenu::onMainWindowClosed() {
    this->show();
}

void MainMenu::on_playButton_clicked() {
    if(mainWindow != nullptr) delete mainWindow;
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
        if (mainWindow != nullptr) delete mainWindow;
        mainWindow = new MainWindow(replayFile, MainWindow::GameMode::Replay);
        connect(mainWindow, SIGNAL(windowClosed()), this, SLOT(onMainWindowClosed()));
        this->hide();
        mainWindow->show();
    }
}

void MainMenu::on_exitButton_clicked() { this->close(); }


QString MainMenu::getLevelPath() { return levelFile; }

void MainMenu::on_mp_mode_selected(bool hosting, std::string host, int port) {
  multiplayerDialog->close();
  if (mainWindow != nullptr) {
    delete mainWindow;
  }
  mainWindow = new MainWindow(levelFile, hosting, host, port);
  connect(mainWindow, SIGNAL(windowClosed()), this, SLOT(onMainWindowClosed()));
  this->hide();
  mainWindow->show();
}
