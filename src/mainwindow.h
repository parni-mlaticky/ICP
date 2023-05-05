#pragma once

#include "drawable.h"
#include "level.h"
#include "logger.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QString &levelFilePath, QWidget *parent = nullptr);
  void keyPressEvent(QKeyEvent *event);
  ~MainWindow() override;
  std::string loadLevelFile(QString levelFilePath);

private:
  void update();
  Drawable *m_scene;
  QGraphicsView *m_view;
  Level *m_level;
  Log::Logger *m_logger;
  Log::Replay *m_replay;
  bool m_levelLoaded;
  int m_log_tick_ms;
  int m_gfx_tick_ms;
  int m_animation_frames;
  int m_frame_counter;
};
