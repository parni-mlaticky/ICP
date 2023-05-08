/**
 * @file logger.h
 * @brief Header for the Logger class
 * @authors Ondřej Zobal, Vladimír Hucovič
 */


#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <exception>
// TODO Comments


namespace Log {
class Logger {
    public:
        Logger();
        void logGrid(std::string record);
        void logRemotePlayer(int id);
        void logDirection(int id, std::pair<int, int> dx_dy);
        void logDirection(int id, int dx, int dy);
        void logTickEnd();
        void logCreation(int id, char type, int x, int y);
        void logRemoval(int id, char type, int x, int y);
        void logMultiplayer();
        std::string getLastTick();
        std::string getCurrentTick();
        std::string getFullLog();
        std::string getGrid();

    protected:
        std::vector<std::string> m_log;
        bool m_grid_set;
        int m_tick_number;
    };

    using ReplayCommand = std::vector<std::string>;
    using ReplayTick = std::vector<ReplayCommand>;
    using ReplayLog = std::vector<ReplayTick>;

    class Replay {
    public:
        Replay(std::string str);
		/** 
		 * @brief Gets the last tick number in the replay
		 * @return The last tick number in the replay
		 * */
        int getMaxTick();
		/** 
		 * @brief Advances the tick counter
		 * */
        void setNextTick();
		/**
		 * @brief Decrements the tick counter
		 * */
        void setPreviousTick();
		/** 
		 * @brief Gets the grid of the level being replayed
		 * @return The grid of the level being replayed as a string
		 * */


		/** 
		 * @brief Reads commands from the replay file and stores them as a ReplayLog
		 * @param str The content of the replay file
		 * @return The ReplayLog containing the commands from the replay file
		 * */
	    ReplayLog* readCommands(std::string str);

		/** 
		 * @brief Appends a tick to the replay log
		 * @param commands The commands to be appended to the replay log
		 * */
		void appendTick(std::string commands); 

		/** 
		 * @brief Gets the grid of the level being replayed
		 * @return The grid of the level being replayed as a string
		 * */
        std::string getGrid();
        bool hasGrid();

		/**
		 * @brief Gets the current tick number
		 * @return The current tick number
		 * */
        int getTick();
	
		/** 
		 * @brief Gets the replay tick from the log on the index currently stored in the tick counter
		 * */
        ReplayTick getLastTick();
		/** 
		 * @brief Returns true if the replay has finished
		 * @return true if the replay has finished, false otherwise
		 * */
        bool isReplayFinished();
		/** 
		 * @brief Returns true if the replay is paused
		 * @return true if the replay is paused, false otherwise
		 * */
		bool isPaused();
		/** 
		 * @brief Toggles the pause state of the replay
		 * @return true if the replay is paused, false otherwise
		 * */
		void togglePause();
		/** 
		 * @brief Toggles the playback direction of the replay
		 * */	
		void togglePlaybackDirection();
		/** 
		 * @brief Checks if the replay is playing backwards
		 * @return true if the replay is playing backwards, false otherwise
		 * */
		bool playingBackwards();
        void stream(std::string message);
        bool getReplaingMultiplayer();
    private:
		/** 
		 * @brief Specifies if the replay is playing backwards
		 * */
		bool m_playing_backwards = false;
		/**
		 * @brief The grid of the level being replayed
		 * */
        std::string m_grid;
        bool m_replaing_multiplayer = false;
        std::string unprocessed;
        ReplayLog m_log;
        int m_tick;
		/** 
		 * @brief Specifies if the replay is paused
		 * */
		bool m_is_paused = false;
    };

    class Remote : private Logger {
    };
}
#endif // LOGGER_H_

