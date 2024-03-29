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


namespace Log {

/**
 * @brief Class for capturing replays
 * */
class Logger {
    public:
        Logger();
        /**
         * @brief Log map
         * @param record Map
         * */
        void logGrid(std::string record);
        /**
         * @brief Logs direction
         * @param id Id of the entity beeing logged
         * @param dx_dy Pair of directions
         * */
        void logDirection(int id, std::pair<int, int> dx_dy);
        /**
         * @brief Logs direction
         * @param id Id of the entity beeing logged
         * @param dx X Direction
         * @param dy Y Direction
         * */
        void logDirection(int id, int dx, int dy);
        /**
         * @brief Logs end of tick
         * */
        void logTickEnd();
        /**
         * @brief Logs creation of a new entity after the start of the game
         * @param id id of the newly created entity
         * @param type Type of the newly created entity, identical with the char given in the level file
         * @param x X coordinate
         * @param y Y coordinate
         * */
        void logCreation(int id, char type, int x, int y);
        /**
         * @brief Logs removal of a new entity after the start of the game
         * @param id Id of the removed entity
         * @param type Type of the removed entity, identical with the char given in the level file
         * @param x X coordinate
         * @param y Y coordinate
         * */
        void logRemoval(int id, char type, int x, int y);
        /**
         * @brief Log that this is a MP game. Has to be called right after logGrid
         * @param id Player id
         * */
        void logMultiplayer();
        /**
         * @brief Returns last tick
         * @return Last tick
         * */
        std::string getLastTick();
        /**
         * @brief Returns an unfinished tick
         * @return Current tick
         * */
        std::string getCurrentTick();
        /**
         * @brief Returns the full log
         * @return Full log
         * */
        std::string getFullLog();
        /**
         * @brief Returns the grid
         * @return The grid
         * */
        std::string getGrid();

    protected:

        /**
         * @brief Vector that stores tick information
         * */
        std::vector<std::string> m_log;
        /**
         * @brief Tells wether the grid has been set already
         * */
        bool m_grid_set;
        /**
         * @brief Number of the current tick
         * */
        int m_tick_number;
    };

    using ReplayCommand = std::vector<std::string>;
    using ReplayTick = std::vector<ReplayCommand>;
    using ReplayLog = std::vector<ReplayTick>;

    /**
     * @brief Class for paring, streaming and replaying logs
     * */
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
		/**
		 * @brief Parse given message and add it to the log. If the message contains an incomplete tick,
		 * it will be stashed and processed when the rest of the tick is given. Also can parse grid.
		 * @param message The mesasge containing logs
		 * */
        void stream(std::string message);
		/**
		 * @brief Returns true if this replay has logs of a multiplayer game. Depends of if the 'M'
		 * command was given.
		 * @return True if this is multiplayer
		 * */
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
        /**
		 * @brief True if this is multiplayer
         * */
        bool m_replaing_multiplayer = false;
        /**
		 * @brief Buffer for unprocessed data
         * */
        std::string unprocessed;
        /**
		 * @brief Parsed logs
         * */
        ReplayLog m_log;
        /**
		 * @brief Current tick
         * */
        int m_tick;
		/** 
		 * @brief Specifies if the replay is paused
		 * */
		bool m_is_paused = false;
    };
}

#endif // LOGGER_H_

