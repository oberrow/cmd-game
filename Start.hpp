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
		Start(int in, std::string par_savegame)
			:getchVal(in)
		{
			if (times == 0)
			{
				this->savegame = par_savegame;
				std::string stringpathexe = std::filesystem::current_path().string() + "\\log.exe";
				/*ShellExecuteA(0, "open", stringpathexe.c_str(), 0, 0, 10);
				if (GetLastError() <= 32)
				{
					int gle = GetLastError();
					std::string str = std::format("Function \"ShellExecuteA\" has failed with error code {}", gle, "!");
					GameInterrupt((LPCSTR)str.c_str());
				}*/

				times++;
				ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
				COORD temp = { 0, 0 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
				l.levelInfo("Enter w, a, s and d to move. Press ctrl + c then any other key to exit \n", 0);
				temp.X = 1;
				temp.Y = 9;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
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
	private:
		std::thread thread1{ [=]() { start(); } }; //lambada 1
		std::thread thread2{ [=]() { MonitorMemoryUsage(); } }; //lambada 2
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