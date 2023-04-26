#pragma once

#include "src/player.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

private:
  QGraphicsScene *m_scene;
  QGraphicsView *m_view;
  Player *m_player;
};
