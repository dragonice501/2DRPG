#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

std::vector<LogEntry> Logger::mLogs;

std::string CurrentDateTimeToString()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string output(30, '\0');
	//std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
	return output;
}

void Logger::Log(const std::string& message)
{
	LogEntry log;
	log.type = LOG_INFO;
	log.message = "LOG: [" + CurrentDateTimeToString() + "] " + message;

	std::cout << "\x1B[32m" << log.message << "\033[0m" << std::endl;

	mLogs.push_back(log);
}

void Logger::Err(const std::string& message)
{
	LogEntry log;
	log.type = LOG_ERROR;
	log.message = "LOG: [" + CurrentDateTimeToString() + "] " + message;

	std::cout << "\x1B[91m" << log.message << "\033[0m" << std::endl;

	mLogs.push_back(log);
}
