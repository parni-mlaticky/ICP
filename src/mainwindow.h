/**
 * @file mainwindow.h
 * @brief Header for MainWindow
 * @authors Ondřej Zobal, Vladimír Hucovič, Petr Kolouch
 */
#pragma once

#include "drawable.h"
#include "level.h"
#include "logger.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include "remote.h"
#include "scene.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <chrono>
#include <iostream>
#include <thread>
#include "logger.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <QMessageBox>

/**
 * @brief The window in which the game will be rendered
 * */
class MainWindow : public QMainWindow {
	Q_OBJECT

		// public members
	public:
		/** Enum specifiying the game mode - play or replay */
		enum class GameMode {
			Play,
			Replay
		};

		// public methods
	public:
		/** 
		 * @brief Initializes the main window 
		 * */
		void initialize();
		/** 
		 * @brief Constructor for the main window, used for singleplayer or replay
		 * */
		explicit MainWindow(QString &levelFilePath,MainWindow::GameMode gameMode, QWidget *parent = nullptr);
		/** 
		 * @brief Constructor for the main window, used for multiplayer
		 * */
		explicit MainWindow(QString &levelFilePath, bool hosting, std::string host, int port, QWidget *parent=nullptr);
		/**
		 * @brief Method called when a key is pressed
		 * */
		void keyPressEvent(QKeyEvent *event) override;

		~MainWindow() override;
		/** 
		 * @brief loads the level into a string from a specified file path 
		 * @param levelFilePath The path to the level file
		 * @return The string representation of the level
		 * */
		std::string loadLevelFile(QString levelFilePath);

		/**
		 * @brief Invoked when a mouse is pressed
		 * @param event Information about the event
		 * */
		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		// protected methods
	protected:
		/** 
		 * @brief Method called when the window is closed
		 * */
		void closeEvent(QCloseEvent *event) override;

signals:
		/** 
		 * @brief Signal emitted when the window is closed
		 * */
		void windowClosed();
		/**
		 * @brief Emitted when the openening of the main menu is requested
		 * */
		void openMainMenu();
		/**
		 * @brief Emitted in order to send a message to the remote party
		 * */
		void sendMessage(std::string);

		// private members
	private:
		/** 
		 * @brief Method used to update the state of the displayed scene
		 * Calls the methods which update the game logic in the background
		 * */
		void update();
		/** 
		 * @brief Scene used to display the game 
		 * */
		Drawable *m_scene;
		/** 
		 * @brief View used to display the game 
		 * */
		QGraphicsView *m_view;

		/** 
		 * @brief The level being played
		 * */
		Level *m_level;
		/** 
		 * @brief The logger used to log the game
		 * */
		Log::Logger *m_logger;
		/** 
		 * @brief The replay used to replay the game
		 * */
		Log::Replay *m_replay;
		/** 
		 * @brief True if the level has been loaded
		 * */
		/** 
		 * @brief The number of milliseconds between each game logic tick
		 * */
		int m_log_tick_ms;
		/** 
		 * @brief The number of milliseconds between each graphics tick
		 * */
		int m_gfx_tick_ms;
		/**
		 * @brief While hosting a multiplayer server, this variable will store
		 * the last message recived from the client.
		 * */
		std::string m_client_message;
		/**
		 * @brief While hosting a multiplayer server, this variable will store
		 * a queue of automatic movements the other player requested.
		 * */
		std::vector<std::string> m_client_queue;

		/**
		 * @brief Number of frames an interpolation should take
		 * */
		int m_animation_frames;
		/**
		 * @brief Frame counter (from 0 to m_animation_frames)
		 * */
		int m_frame_counter;
		/** 
		 * @brief Specifies the game mode - play or replay
		 * */
		MainWindow::GameMode gamemode;
		/** 
		 * @brief Timer used to update the game logic
		 * */
		QTimer *timer;
		/**
		 * @brief Reference to the client is stored here when the game is played in multiplayer mode and this session acts as the client
		 * */
		Remote* mp_client;
		/**
		 * @brief Reference to the server is stored here when the game is played in multiplayer mode and this session acts as the server
		 * */
		Remote* mp_server;
		/**
		 * @brief If true, the game is paused
		 * */
		bool m_replay_paused;
		public slots:
			/**
			 * @brief Processes newly recived messages
			 * */
			void onRecive(std::string message);
		/**
		 * @brief Called when the server connects to the client
		 * */
		void on_connected_to_client();
		/**
		 * @brief Called when the client to server
		 * */
		void on_connected_to_server();
		/**
		 * @brief Called when the other party disconnects
		 * */
		void onDisconnect();
};
