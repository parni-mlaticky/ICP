#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include "server.h"
#include "client.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QDir::setCurrent(QCoreApplication::applicationDirPath());
  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
