#include "log.h"

namespace game {
	void Log::levelInfo(std::string message)
	{
		game::colorAttributes color{ FOREGROUND_GREEN };
		if (m_level <= 0)
			std::cout << "[INFO] " <<  message;
		else
			return;
	}
	void Log::levelWarn(std::string message)
	{
		game::colorAttributes color{ (DWORD)14 };
		if (m_level <= 1)
			std::cout << "[WARNING] " << message;
		else
			return;
	}
	void Log::levelError(std::string message)
	{
		game::colorAttributes color{ FOREGROUND_RED | FOREGROUND_INTENSITY };
		if (m_level <= 2)
			std::cerr << "[ERROR] " << message;
		else
			return;
	}
	void Log::setLevel(int level)
	{
		m_level = level;
	}
}                                                                                                                                                                                                                                                                                 