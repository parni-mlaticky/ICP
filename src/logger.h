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
        int getMaxTick();
        void setTick(int tick);
        void setNextTick();
        void setPreviousTick();
        std::string getGrid();
        bool hasGrid();
        int getTick();
        ReplayTick getLastTick();
        bool isReplayFinished();
		bool isPaused();
		void togglePause();
		void togglePlaybackDirection();
		bool playingBackwards();
        void stream(std::string message);
    private:
		bool m_playing_backwards = false;
        std::string m_grid;
        std::string unprocessed;
        ReplayLog m_log;
        int m_tick;
		bool m_is_paused = false;
    };

    class Remote : private Logger {
    };
}
#endif // LOGGER_H_
