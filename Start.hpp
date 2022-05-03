#if defined(_WIN64) && STATE && CMDGAME
#pragma once
#include "includes.hpp"
#include "movements.hpp"
#include "log.hpp"
#include "place.hpp"
#include "Colisions.hpp"
#include "Config.hpp"
#include "Generate.hpp"
#include "Gravity.hpp"
#include "ExperimentStore.hpp"

namespace game {
	class Start {
	public:
		Log l{ Log::levelInfoId };
		inline static bool ctrlc = false;
		static inline std::string savegame = "";
		
		Start(int in, std::string par_savegame, bool par_use_colisions, game::ExperimentStore experments)
			:m_Exp(experments)
		{
			times++;
			getchVal = in;
			if (times == 0)
			{
				use_colisions = par_use_colisions;
				this->savegame = par_savegame;
				util::clear();
				ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
				COORD temp = { 0, 0 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
				l.levelInfo("Enter w, a, s and d to move. Press ctrl + c to exit\n", PRINT_ON_DEFAULT_CONSOLE);
				temp.X = 1;
				temp.Y = 8;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
			}
			else if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &in_Buffer))
			{
					l.levelError("An error has occured. Function GetConsoleScreenBufferInfo() has failed because of an unspecified error", PRINT_ON_DEFAULT_CONSOLE);
					ctrlc = true;
			}
		}
		~Start() {
			thread1.detach();
			thread2.detach();
		}
		static inline std::string GetCurrentBlock();
	private:
		game::ExperimentStore m_Exp = { 0 };
		static inline int times3 = 0;
		inline static COORD maxConsoleSize = { 0, 0 };
		void save();
		bool hasBeenModified = false;
		int preFileSize;
		static inline bool use_colisions = true;
		bool isPlacingBlock = false;
		std::thread thread1{ [=]() { start(); } }; //lambada 1
		std::thread thread2{ [=]() { MonitorMemoryUsage(); } }; //lambada 2
		void start();
		void generate(/*int seed*/);
		void dispatch();
		void MonitorMemoryUsage();
		inline static int times = -1;
		static inline int times2 = 0;
		int getchVal{};
		inline static std::string sStream;
		void setFontSize(int FontSize);
		CONSOLE_SCREEN_BUFFER_INFO in_Buffer{};
	};
}
#endif