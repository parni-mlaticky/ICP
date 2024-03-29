/** *
 * @file logger.cpp
 * @brief Implementation of the Logger class
 * @details This file contains the implementation of the Logger class, which handles the logging of the game. If also contains the
 * implementation of the Replay class, which handles the replaying of a recorded game.
 * @authors Ondřej Zobal, Vladimír Hucovič
 */

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

void Logger::logMultiplayer() {
	this->m_log[m_tick_number++].append("M\n");
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
	this->m_grid = "";
	this->m_log = ReplayLog();
	this->stream(str);
}

void Replay::stream(std::string message) {
	message = this->unprocessed + message;
	auto iter = message.begin();

	// If grid is not yet set, recive grid.
	if (m_grid == "") {
		std::string word = "";
		// Reading grid
		int lines = -1;
		while (iter != message.end()) {
			word += *iter;
			if (*iter == ' ' && lines == -1) {
				lines = stoi(word)+1;
				continue;
			}
			lines -= *iter == '\n';
			if (lines == 0) {
				std::cerr << "Replay parse: Grid recived in full" << std::endl;
				m_grid = word;
				break;
			}
			iter++;
		}

		// If we didn't recive the whole grid
		if (lines != 0) {
			std::cerr << "Replay parse: Incomplete grid, stashing..." << std::endl;
			this->unprocessed = message; // message.substr(iter - message.begin());
			return;
		}
	}

	// Recive commands.
	std::string word = "";
	ReplayCommand command = ReplayCommand();
	ReplayTick tick = ReplayTick();
	auto parsed_up_to = iter;

	iter -= 1;
	while (++iter != message.end()) {
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

		if (*iter == 'M') {
			this->m_replaing_multiplayer = true;
		}

		if (*iter == ' ') {
			if (word != "") {
				command.push_back(word);
				word = "";
			}
			continue;
		}

		word += *iter;
		if (*iter == 'T') {
			word = "";
			if (command.size() > 0) {
				tick.push_back(command);
			}
			m_log.push_back(tick);
			command = ReplayCommand();
			tick = ReplayTick();

			// Skipping the trailing endline.
			parsed_up_to = ++iter;
			if (iter == message.end()) {
				break;
			}
			continue;
		}
	}

	// Moving iter to the next character that wasn't scanned yet.
	if (iter != message.end()) {
		++iter;
	}

	// Stashing away data that were not yet made into a full tick for another call.
	if (parsed_up_to != iter) {
		this->unprocessed = message.substr(parsed_up_to - message.begin());
		this->unprocessed = (this->unprocessed == "\n") ? "" : this->unprocessed;
		std::cerr << "Replay: Stashed " << this->unprocessed.size() << "B of incomplete commands." << std::endl;
		std::cerr << this->unprocessed << std::endl;
	}
	else {
		this->unprocessed = "";
	}
}

std::string Replay::getGrid() {
	return this->m_grid;
}

bool Replay::hasGrid() {
	return m_grid != "";
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

void Replay::togglePause(){
	this->m_is_paused = !this->m_is_paused;
}

bool Replay::playingBackwards(){
	return this->m_playing_backwards;
}

void Replay::togglePlaybackDirection(){
	this->m_playing_backwards = !this->m_playing_backwards;
}

bool Replay::getReplaingMultiplayer() {
	return this->m_replaing_multiplayer;
}
