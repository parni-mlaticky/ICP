#include "logger.h"

using namespace Log;

Logger::Logger() : m_grid_set(false), m_tick_number(1) {
    m_log = std::vector<std::string>();
    // At index 0 we store the grid.
    m_log.push_back("");
    // At index 1 onwards we store the replay.
    m_log.push_back("");
}

void Logger::logGrid(std::string record) {
    if (m_grid_set) {
        std::cerr << "Attempted to log grid more than once" << std::endl;
        throw new std::exception;
    }

    this->m_log[0] = record;
    m_grid_set = true;
}

void Logger::logRemotePlayer(int id) {
    this->m_log[m_tick_number].append("Y " + std::to_string(id) + "\n");
}

void Logger::logDirection(int id, std::pair<int, int> dx_dy) {
    this->m_log[m_tick_number].append("D " + std::to_string(id) + " " + \
                                      std::to_string(dx_dy.first) + " " +\
                                      std::to_string(dx_dy.second) + "\n");
}

void Logger::logDirection(int id, int dx, int dy) {
    this->m_log[m_tick_number].append("D " + std::to_string(id) + " " + std::to_string(dx) + " " + std::to_string(dy) + "\n");
}

void Logger::logTickEnd() {
    this->m_log[m_tick_number++].append("T\n");
    this->m_log.push_back("");
}

void Logger::logCreation(int id, char type, int x, int y) {
    this->m_log[m_tick_number].append("C " + std::to_string(id) + " " + type + " " + std::to_string(x) + " " + std::to_string(y) + "\n");
}
void Logger::logRemoval(int id, char type, int x, int y) {
    this->m_log[m_tick_number].append("R " + std::to_string(id) + " " + type + " " + std::to_string(x) + " " + std::to_string(y) + "\n");
}

std::string Logger::getLastTick() {
    if (m_tick_number == 1) {
        return "";
    }

    return this->m_log[m_tick_number-1];
}

std::string Logger::getCurrentTick() {
    return this->m_log[m_tick_number];
}

std::string Logger::getFullLog() {
    if (!m_grid_set) {
        std::cerr << "Attempted to get full level log with grid unset!" << std::endl;
        throw new std::exception;
    }
    std::string str = "";
    for (auto tick : m_log) {
        str += tick;
    }
    return str;
}

std::string Logger::getGrid() {
    if (!m_grid_set) {
        std::cerr << "Attempted to get grid before setting it!" << std::endl;
        exit(1);
    }
    return m_log[0];
}

Replay::Replay(std::string str) : m_tick(0) {
    std::string word = "";
    // Reading grid
    int lines = -1;
    for (auto ch : str) {
        word += ch;
        if (ch == ' ' && lines == -1) {
            lines = stoi(word)+1;
            continue;
        }
        lines -= ch == '\n';
        if (lines == 0) {
            break;
        }
    }

    m_grid = word;
    std::cerr << str[word.size()] << "xdd\n";
    std::string strr = std::string(&str.c_str()[word.size()-2]);
    m_log = *readCommands(strr);
}

ReplayLog* Replay::readCommands(std::string str) {
    ReplayLog* log = new ReplayLog();
    std::string word = "";
    ReplayCommand command = ReplayCommand();
    ReplayTick tick = ReplayTick();

    // Reading commands
    auto iter = str.begin();
    while (iter != str.end()) {
        iter++;
        if (*iter == '\n') {
            if (word != "") {
                command.push_back(word);
                word = "";
            }
            if (command.size() > 0) {
                tick.push_back(command);
            }
            command = ReplayCommand();
            continue;
        }

        if (*iter == ' ') {
            if (word != "") {
                command.push_back(word);
                word = "";
            }
            continue;
        }

        if (*iter == 'T') {
            word = "";
            if (command.size() > 0) {
                tick.push_back(command);
            }
            log->push_back(tick);
            command = ReplayCommand();
            tick = ReplayTick();
            continue;
        }

        word += *iter;
    }

    return log;
}

std::string Replay::getGrid() {
    return this->m_grid;
}

int Replay::getTick() {
    return this->m_tick;
}

int Replay::getMaxTick() {
    return this->m_log.size();
}

bool Replay::isPaused(){
	return this->m_is_paused;
}

ReplayTick Replay::getLastTick() {
	std::cerr << "Getting last tick number : " << this->m_tick << std::endl;
    return this->m_log[this->m_tick];
}

void Replay::setNextTick() {
    this->m_tick++;
}

void Replay::setPreviousTick(){
	if(this->m_tick > 0){
		this->m_tick--;
	}
}

bool Replay::isReplayFinished() {
    return this->m_tick == (int) m_log.size();
}

void Replay::appendTick(std::string commands) {
    auto log = readCommands(commands);

    for (auto entry : *log) {
        m_log.push_back(entry);
    }
}
void Replay::togglePause(){
	this->m_is_paused = !this->m_is_paused;
}

bool Replay::playingBackwards(){
	return this->m_playing_backwards;
}

void Replay::togglePlaybackDirection(){
	this->m_playing_backwards = !this->m_playing_backwards;
}
