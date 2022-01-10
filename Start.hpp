#pragma once
#include "includes.hpp"
#include "movements.hpp"
#include "log.hpp"
#include "place.hpp"
#include "Colisions.hpp"
#include "Config.hpp"
#include "Generate.hpp"

namespace game {
	class Start {
	public:
		Log l{ Log::levelInfoId };
		static inline std::string savegame = "";
		Start(int in, std::string savegame)
			:getchVal(in)
		{
			if (times == 0)
			{
				times++;
				ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
				COORD temp = { 0, 0 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
				l.levelInfo("Enter w, a, s and d to move. Press ctrl + c then any other key to exit \n");
				temp.X = 1;
				temp.Y = 9;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
			}
			else if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &in_Buffer))
			{
				l.levelError("An error has occured. Function GetConsoleScreenBufferInfo() has failed because of an unspecified error");
				game::GlobalVars::endProg = true;
			}
		}
		~Start() {
			thread1.detach();
			thread2.detach();
		}
	private:
		std::thread thread1{ [=]() { start(); } };
		std::thread thread2{ [=]() { MonitorMemoryUsage(); } };
		void save();
		void start();
		void generate(/*int seed*/);
		void dispatch();
		void MonitorMemoryUsage();
		inline static int times = 0;
		static inline int times2 = 0;
		int getchVal{};
		inline static std::string sStream;
		void setFontSize(int FontSize);
		CONSOLE_SCREEN_BUFFER_INFO in_Buffer{};
	};
}                                                                                                                                        