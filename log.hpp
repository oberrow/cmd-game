#pragma once
#include "includes.h"
#include "colorAttributes.h"

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
		void levelInfo(std::string message);
		void levelWarn(std::string message);
		void levelError(std::string message);
		void setLevel(int level);
		Log(int level)
		{
			m_level = level;
		}
	};
}
