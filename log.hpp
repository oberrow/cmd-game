#pragma once
#include "includes.hpp"
#include "colorAttributes.hpp"

namespace game
{
	class Log
	{
	private:
		inline static int m_level;
	public:
		static const int levelInfoId = 0;
		static const int levelWarningId = 1;
		static const int levelErrorId = 2;
		void levelInfo(std::string message, bool printToConsole = 1);
		void levelWarn(std::string message, bool printToConsole = 1);
		void levelError(std::string message, bool printToConsole = 1);
		void setLevel(int level);
		Log(int level)
		{
			m_level = level;
			if (!std::filesystem::exists("log.txt"))
			{
				levelError("File \" log.txt \" doesn't exist!", false);
				return;

			}
		}
	};
}