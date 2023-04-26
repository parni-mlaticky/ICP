cmake_minimum_required(VERSION 3.14)

project(parni-pacman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(
  Qt5
  COMPONENTS Core Widgets
  REQUIRED)

add_executable(
  parni-pacman
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  src/player.cpp
  src/player.h
  src/ghost.h
  src/ghost.cpp
  src/key.h
  src/key.cpp
  src/wall.h
  src/wall.cpp
  src/finish.h
  src/finish.cpp
  src/level.h
  src/level.cpp)

target_link_libraries(parni-pacman PRIVATE Qt5::Core Qt5::Widgets)
