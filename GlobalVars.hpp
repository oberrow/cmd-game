#pragma once
#include <fstream>
#include <windows.h>
#include <chrono>
#include <thread>

#define OUT_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)
#define WHILETRUE while(true)
#define Struct struct

namespace game {
	inline void GameInterrupt(LPCSTR message = "Interrupted...") {
		MessageBoxA(NULL, message, "Game Interrupt system!", MB_ICONERROR);
		std::ofstream of{ "log.txt", std::ofstream::out | std::ofstream::trunc };
		of << "[END]";
		of.close();
		using namespace std::literals;
		std::this_thread::sleep_for(105ms);
		std::ofstream of2{ "log.txt", std::ofstream::out | std::ofstream::trunc };
		of2.close();
		throw std::exception();
	}
	struct DeleteLog
	{
		DeleteLog() = default;
		~DeleteLog() 
		{
			std::ofstream of{ "log.txt", std::ofstream::out | std::ofstream::trunc };
			of << "[END]";
			of.close();
			using namespace std::literals;
			std::this_thread::sleep_for(105ms);
			std::ofstream of2{ "log.txt", std::ofstream::out | std::ofstream::trunc };
			of2.close();
		}
	};
	namespace GlobalVars {
		static bool BackSpace = false;
	}
}