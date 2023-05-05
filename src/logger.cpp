#include "logger.h"
#include <exception>
#include <iostream>
#include <vector>

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

Replay::Replay(std::string str) : m_tick(0) {
    m_log = ReplayLog();
    std::string word = "";
    ReplayCommand command = ReplayCommand();
    ReplayTick tick = ReplayTick();

    // Reading grid
    int lines = -1;
    for (auto ch : str) {
        word += ch;
        if (ch == ' ' && lines == -1) {
            lines = atoi(word.c_str())+1;
            continue;
        }
        lines -= ch == '\n';
        if (lines == 0) {
            break;
        }
    }

    m_grid = word;
    word = "";

    // Reading commands
    auto iter = str.begin() + m_grid.size()-1;
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
            m_log.push_back(tick);
            command = ReplayCommand();
            tick = ReplayTick();
            continue;
        }

        word += *iter;
    }
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

ReplayTick Replay::getLastTick() {
    return this->m_log[this->m_tick];
}

void Replay::setNextTick() {
    this->m_tick++;
}

bool Replay::isReplayFinished() {
    return this->m_tick == (int) m_log.size();
}
