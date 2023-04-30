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
  COMPONENTS Core Widgets Network
  REQUIRED)

add_executable(
  parni-pacman
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/mainwindow.ui
  src/player.cpp
  src/player.h
  src/ghost.h
  src/ghost.cpp
  src/key.h
  src/key.cpp
  src/wall.h
  src/wall.cpp
  src/floor.h
  src/floor.cpp
  src/finish.h
  src/finish.cpp
  src/level.h
  src/level.cpp
  src/entity.h
  src/entity.cpp
  src/server.cpp
  src/client.cpp
  )

target_link_libraries(parni-pacman PRIVATE Qt5::Core Qt5::Widgets Qt5::Network)
