#pragma once
#include "includes.hpp"
#include "movements.hpp"
#include "log.hpp"
#include "place.hpp"
#include "Colisions.hpp"
#include "Config.hpp"
#include "Generate.hpp"
#include "Entity.hpp"

namespace game {
	class Start {
	public:
		Log l{ Log::levelInfoId };
		inline static bool ctrlc = false;
		static inline std::string savegame = "";
		Start(int in, std::string par_savegame, bool par_use_colisions)
			:getchVal(in)
		{
			if (times == 0)
			{
				use_colisions = par_use_colisions;
				system("cls");
				this->savegame = par_savegame;
				//ShellExecuteA(NULL, "open", "log.exe", NULL, NULL, SW_SHOWMINIMIZED);
				times++;
				ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
				COORD temp = { 0, 0 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
				l.levelInfo("Enter w, a, s and d to move. Press ctrl + c to exit\n", PRINT_ON_DEFAULT_CONSOLE);
				temp.X = 1;
				temp.Y = 8;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				generate();
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				game::Generate g{ savegame.c_str(), in_Buffer };
			}
			else if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &in_Buffer))
			{
				l.levelError("An error has occured. Function GetConsoleScreenBufferInfo() has failed because of an unspecified error", true);
				ctrlc = true;
			}
		}
		~Start() {
			thread1.detach();
			thread2.detach();
		}
		//VOID WINAPI SetConsoleColors(WORD);
	private:
		static inline bool use_colisions = true;
		std::string GetCurrentBlock();
		bool isPlacingBlock = false;
		std::thread thread1{ [=]() { start(); } }; //lambada 1
		std::thread thread2{ [=]() { MonitorMemoryUsage(); } }; //lambada 2
		auto read_file(std::string_view)->std::string;
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