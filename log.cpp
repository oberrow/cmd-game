#include "log.hpp"

namespace game {
	void Log::levelInfo(std::string message, bool printToConsole)
	{
		game::colorAttributes color{ GREEN };
		if (m_level <= 0 && !printToConsole)
			std::cout << "[INFO] " <<  message;
		else if (m_level <= 0 && printToConsole)
		{
			std::ofstream of{ "log.txt", std::ios::out | std::ios::app };
			of << "\n[INFO] " << message;
		}
		else
			return;
	}
	void Log::levelWarn(std::string message, bool printToConsole)
	{
		game::colorAttributes color{ YELLOW };
		if (m_level <= 1 && printToConsole == false)
			std::cout << "[WARNING] " << message;
		else if (m_level <= 1 && printToConsole)
		{
			std::ofstream of{ "log.txt", std::ios::out | std::ios::app };
			of << "\n[WARNING] " << message;
		}
		else
			return;
	}
	void Log::levelError(std::string message, bool printToConsole)
	{
		game::colorAttributes color{ RED | FOREGROUND_INTENSITY };
		if (m_level <= 2 && printToConsole == false)
			std::cerr << "[ERROR] " << message;
		else if (m_level <= 2 && printToConsole)
		{
			std::ofstream of{ "log.txt", std::ios::out | std::ios::app };
			of << "\n[ERROR] " << message;
		}
		else
			return;
	}
	void Log::setLevel(int level)
	{
		m_level = level;
	}
}                                                                                                                                                                                                                                                                                 