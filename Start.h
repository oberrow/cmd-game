#include "includes.h"
#include "movements.h"
#include "log.h"
#include "place.hpp"
#include "Colisions.h"
#pragma once
namespace game {
	class Start {
	public:
		Log l{ Log::levelInfoId };
		Start(int in)
			:getchVal(in)
		{
			
			
			if (times == 0)
			{
				ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
				COORD temp = { 0, 0 };
				times++;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
				l.levelInfo("Enter w, a, s and d to move\n");
				temp = { 1, 0 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
			}
			else if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &in_Buffer))
			{
				l.levelError("An error has occured. Function GetConsoleScreenBufferInfo() has failed because of an unspecified error");
				_STD terminate();
			}
		}
		~Start() {
			thread1.detach();
			thread2.detach();
		}
	private:
		std::thread thread1{ [=]() { start(); } };
		std::thread thread2{ [=]() { MonitorMemoryUsage(); } };
		void start();
		void generate(/*int seed*/);
		void MonitorMemoryUsage();
		inline static int times = 0;
		static inline int times2 = 0;
		int getchVal{};
		void setFontSize(int FontSize);
		CONSOLE_SCREEN_BUFFER_INFO in_Buffer{};
		void dispatch();
	};
}                                                                                                                                        
