#if defined(_WIN64) && STATE && CMDGAME
#pragma once
#include "includes.hpp"
#include "colorAttributes.hpp"

namespace game
{
	class Log
	{
	private:
		int m_level;
	public:
		static const int levelInfoId = 0;
		static const int levelWarningId = 1;
		static const int levelErrorId = 2;
		void levelInfo(std::string message, bool printToConsole = 1);
		void levelWarn(std::string message, bool printToConsole = 1);
		void levelError(std::string message, bool printToConsole = 1);
		void setLevel(int level);
		Log(int level)
			:m_level{level}
		{
			if (!std::filesystem::exists("log.txt"))
			{
				levelError("File \" log.txt \" doesn't exist!", false);
				return;
			}
		}
	};
	class Chat
	{
	private:
		std::string m_worldDir{};
		std::string m_chatFile{};
		bool m_state = true;
	public:
		bool chat(std::string message);
		Chat(std::string worldDir)
			:m_worldDir(worldDir)
		{
			if(std::filesystem::exists(m_worldDir))
			{ 
				std::string s = m_worldDir;
				s.append("\\chat.txt");
				m_chatFile.assign(s);
			}
			if (!std::filesystem::exists(m_chatFile))
			{
				Log l = Log::levelInfoId;
				l.levelError(std::format("File {}", m_chatFile, " doesn't exist!"));
				m_state = false;
			}
		}
	};
}
#endif