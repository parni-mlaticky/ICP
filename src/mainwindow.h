#pragma once

#include "level.h"
#include "drawable.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QString &levelFilePath, QWidget *parent = nullptr);
  void keyPressEvent(QKeyEvent* event);
  ~MainWindow() override;

private:
  void update();
  Drawable* m_scene;
  QGraphicsView *m_view;
  Level *m_level;
  bool m_levelLoaded;
  int m_log_tick_ms;
  int m_gfx_tick_ms;
  int m_animation_frames;
  int m_frame_counter;
};
