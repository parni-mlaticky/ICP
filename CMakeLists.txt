cmake_minimum_required(VERSION 3.14)

project(parni-pacman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER g++)

add_compile_options(-g)

find_package(
  Qt5
  COMPONENTS Core Widgets Network
  REQUIRED)

<<<<<<< Updated upstream
set(SOURCES
    src/entity.cpp
    src/finish.cpp
    src/ghost.cpp
    src/key.cpp
    src/level.cpp
    src/main.cpp
    src/mainmenu.cpp
    src/mainwindow.cpp
    src/player.cpp
    src/floor.cpp
    src/wall.cpp
	src/cell.cpp
	)
=======
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
  src/cell.cpp
  )
>>>>>>> Stashed changes

set(HEADERS
    src/entity.h
    src/finish.h
    src/ghost.h
    src/key.h
    src/level.h
    src/mainmenu.h
    src/mainwindow.h
    src/player.h
    src/floor.h
    src/wall.h
	src/cell.h)

set(UI src/mainwindow.ui src/mainmenu.ui)

# Save the original CMAKE_CURRENT_BINARY_DIR and change it to the src directory
set(ORIGINAL_CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

qt5_wrap_ui(UI_HEADERS ${UI})

# Restore the original CMAKE_CURRENT_BINARY_DIR
set(CMAKE_CURRENT_BINARY_DIR ${ORIGINAL_CMAKE_CURRENT_BINARY_DIR})

add_executable(parni-pacman ${SOURCES} ${HEADERS} ${UI_HEADERS})
target_link_libraries(parni-pacman PRIVATE Qt5::Core Qt5::Widgets Qt5::Network)
