#pragma once
#include <fstream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <vector>

#define OUT_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)
#define WHILETRUE while(true)
#define Struct struct
#define PRINT_ON_DEFAULT_CONSOLE 0
#define PRINT_ON_LOG_CONSOLE 1
#define OPTION_LOAD 1
#define OPTION_NEW 2
#define OPTION_DELETE 2


inline HANDLE GetOutputHandle()
{
	return(GetStdHandle(STD_OUTPUT_HANDLE));
}
namespace game {
	template<typename T>
	// Only works with c style array's
	inline bool in_array(T* _array, T _is, size_t size)
	{
		bool no = false;
		for (int i = 0; i < size; i++)
		{
			if (_array[i] == _is)
			{
				return true;
			}
			else {
				no = true;
			}
		}
		if (no == true)
		{
			return false;
		}
	}
	template<typename T>
	// Only works with std::Vector
	inline bool in_vector(std::vector<T> _array, T _is)
	{
		bool no = false;
		for (int i = 0; i < _array.size(); i++)
		{
			if (_array[i] == _is)
			{
				return true;
			}
			else {
				no = true;
			}
		}
		if (no == true)
		{
			return false;
		}
	}
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
			std::this_thread::sleep_for(30ms);
			of.open("log.txt", std::ofstream::out | std::ofstream::trunc);
			of.close();
		}
	};
	namespace GlobalVars {
		static bool BackSpace = false;
	}
}