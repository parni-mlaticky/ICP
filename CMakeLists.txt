cmake_minimum_required(VERSION 3.14)

project(parni-pacman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(parni-pacman
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  src/game_model.cpp
  src/game_model.h
  src/game_view.cpp
  src/game_view.h
  src/game_controller.cpp
  src/game_controller.h
  )

target_link_libraries(parni-pacman PRIVATE Qt5::Core Qt5::Widgets)
