#pragma once
#include "includes.h"
#include "log.hpp"

namespace game {
	class Colisions
	{
		std::string* output = new std::string;
		Log l{ Log::levelInfoId };
	public:
		~Colisions() {
			delete output;
		}
		Colisions(CONSOLE_SCREEN_BUFFER_INFO buff)
		{
			/*if (ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &c, size, buff.dwCursorPosition, &buff.srWindow) == 0)
			{
				l.levelError("An error has occured! Function ReadConsoleOutputA() has failed\n");
				DWORD lerr = GetLastError();
				l.levelInfo("Possible error code is " + std::to_string(lerr) + '\n');
			}*/
			std::stringbuf sbuf(std::ios::out); // create a stringbuf
			auto oldbuf = std::cout.rdbuf(std::addressof(sbuf)); // associate the stringbuf with std::cout

			std::cout << std::flush;
			std::cout.rdbuf(oldbuf); // restore cout's original buffer

			*output = std::string(sbuf.str()); // get a copy of the underlying string
			for (char& c : *output) c = std::toupper(c); // modify it
			buff.dwCursorPosition.Y--;
			if (*output == "[]" || *output == "[" || *output == "]")
			{
				if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), buff.dwCursorPosition)) {
					l.levelError("An error has occured! Function SetConsoleCursorPosition has failed");
				}
			};
		}
	};
}
