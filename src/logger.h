#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <utility>
#include <vector>

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
        std::string getGrid();
        int getTick();
        ReplayTick getLastTick();
        bool isReplayFinished();
        void appendTick(std::string commands);
    private:
        ReplayLog* readCommands(std::string str);
        std::string m_grid;
        ReplayLog m_log;
        int m_tick;
    };

    class Remote : private Logger {
    };
}
#endif // LOGGER_H_
