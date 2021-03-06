#if defined(_WIN64) && STATE && CMDGAME
#pragma once
#include "includes.hpp"

#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15

namespace game {
	enum colors
	{
		black,
		blue,
		green,
		cyan,
		red,
		magenta,
		brown,
		lightgray,
		darkgray,
		lightblue,
		lightgreen,
		lightcyan,
		lightred,
		lightmagenta,
		yellow,
		white
	};
	struct colorAttributes {
		colorAttributes(WORD attrib) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attrib);
		}
		~colorAttributes() {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}
	};
}     
#endif