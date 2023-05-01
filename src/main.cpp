#include "mainmenu.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainMenu mainMenu;
  mainMenu.show();
  return app.exec();
}
