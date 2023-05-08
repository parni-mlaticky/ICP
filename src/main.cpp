/** 
 * @file main.cpp
 * @brief Main file of the game
 * @details This file contains the main function of the game. It creates the main menu and shows it.
 * @authors Vladimír Hucovič, Ondřej Zobal, Petr Kolouch
 * */

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
