#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

  setWindowTitle("Parni pacman");
  setFixedSize(800, 600);
}

MainWindow::~MainWindow() = default;
