
// 0x01 is game 0x00 is testing
#define STATE 			0x01
#define CMDGAME 		STATE
#define ENTITY_TESTING	0x00

#if !STATE || !CMDGAME
#include <stdio.h>
#include <assert.h>

namespace game
{
	inline void PutStateMacroToOne()
	{
		printf_s("\nGo to GlobalVars.hpp and change the \"STATE\" or the \"CMDGAME\" macro to 0x01\n");
		assert(0);
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
}
#endif


#if defined(_WIN64) && STATE && CMDGAME
#pragma once
#define WIN32_LEAN_AND_MEAN

#include <fstream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <vector>
#include "colorAttributes.hpp"
#include "log.hpp"

#define OUT_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)
#define WHILETRUE while(true)
#define Struct struct
#define PRINT_ON_DEFAULT_CONSOLE 0
#define PRINT_ON_LOG_CONSOLE 1
#define OPTION_LOAD 1
#define OPTION_NEW 2
#define OPTION_DELETE 2
#define COPY_CONSTRUCTER(cls_name) cls_name(const cls_name& copy)
#define ASSIGNMENT_OPERATOR(cls_name) cls_name& operator=(const cls_name& copy)
#define NODISCARD(rettype, funcname) [[nodiscard]] rettype funcname

inline HANDLE GetOutputHandle()
{
	return(GetStdHandle(STD_OUTPUT_HANDLE));
}
namespace game {
	// The unsigned format of the keys to control the game
	enum Keys
	{
		W = 'W',
		S = 'S',
		A = 'A',
		D = 'D',
		w = 'w',
		s = 's',
		a = 'a',
		d = 'd',
		P = 'P',
		L = 'L',
		B = 'B',
		G = 'G',
		R = 'R',
		p = 'p',
		l = 'l',
		b = 'b',
		g = 'g',
		r = 'r',
		space = ' ',
		backspace = '\b'
	};
	// Names and colors of the blocks in the game
	enum blocks
	{
		grass = LIGHTGREEN,
		water = BLUE,
		bedrock = LIGHTBLUE,
		log = BROWN,
		rock = LIGHTGRAY
	};
	// Makes a message box and ends the program using __fastfail(0);
	inline void GameInterrupt(LPCSTR message = "Error!") {
		MessageBoxA(NULL, message, "Game Interrupt system!", MB_ICONERROR);
		std::ofstream of{ "log.txt", std::ofstream::out | std::ofstream::trunc };
		of << "[END]";
		of.close();
		using namespace std::literals;
		std::this_thread::sleep_for(30ms);
		std::ofstream of2{ "log.txt", std::ofstream::out | std::ofstream::trunc };
		of2.close();
		__fastfail(0);
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
	};/*
	class block
	{
	private:
		const char* m_id = "NULL";
		COORD m_coord = { 0, 0 };
		bool m_state = goodbit;
		WORD m_color{};
	public:
		const bool goodbit = 1;
		const bool badbit = 0;
		inline static const char* const BlockIds[6] = { "NULL", "GREENERY", "ROCK", "BEDROCK", "WATER", "LOG" };
		bool GetState() { return m_state; }
		const char* const& GetCurrentBlock() { return m_id; }
		ASSIGNMENT_OPERATOR(block)
		{
			if (&copy != nullptr)
			{
				m_color = copy.m_color;
				m_coord = copy.m_coord;
				m_id = copy.m_id;
				m_state = copy.m_state;
			}
			else
			{
				m_color = 0;
				m_coord = COORD(0, 0);
				m_id = "NULL";
				m_state = false;
				return *this;
			}
			return *this;
		}
		COPY_CONSTRUCTER(block)
		{
			if (&copy != nullptr)
			{
				m_color = copy.m_color;
				m_coord = copy.m_coord;
				m_id = copy.m_id;
				m_state = copy.m_state;
			}
			else
			{
				m_color = 0;
				m_coord = COORD(0, 0);
				m_id = "NULL";
				m_state = false;
			}
		}
		block(const char* id, COORD coord)
			:m_id(id), m_coord(coord)
		{
			if (m_id == BlockIds[0] || id == BlockIds[0])
			{
				m_state = badbit;
				return;
			}
			if (m_id == "GREENERY")
			{
				m_color = blocks::grass;
			}
			else if (m_id == "ROCK")
			{
				m_color = blocks::rock;
			}
			else if (m_id == "BEDROCK")
			{
				m_color = blocks::bedrock;
			}
			else if (m_id == "WATER")
			{
				m_color = blocks::water;
			}
			else if (m_id == "LOG")
			{
				m_color = blocks::log;
			}
			else
			{
				Log l = Log::levelErrorId;
				l.levelError("Invalid Block Id!", PRINT_ON_LOG_CONSOLE);
			}
		}
		block() = default;
	};*/
	namespace GlobalVars {
		static bool BackSpace = false;
		/*static std::map<std::string, block> world_map;*/
	}
}
#endif