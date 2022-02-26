#pragma once
#include "includes.hpp"
#include "log.hpp"

namespace game {
	class Colisions
	{
    private:
		Log l{ Log::levelInfoId };
        TCHAR strFromConsole[1];
        TCHAR strFromConsoleUp[1];
        WORD lpAttrib[1];
        WORD lpAttrib2[1];
	public:
        COORD newPos{};
        bool found = false;
        bool isBlockAbove = false;
		Colisions(CONSOLE_SCREEN_BUFFER_INFO buff)
		{
#define RCOA ReadConsoleOutputAttribute
#define RCOC ReadConsoleOutputCharacterW
            COORD pos = buff.dwCursorPosition;
            DWORD dwChars1;
            DWORD dwChars2;
            DWORD dwAttribs1;
            RCOC(
                GetStdHandle(STD_OUTPUT_HANDLE),
                strFromConsole,
                1,
                pos,
                &dwChars1);
            RCOA(
            GetStdHandle(STD_OUTPUT_HANDLE),
            lpAttrib,
            1,
            pos,
            &dwAttribs1
            );
            COORD pos2 = buff.dwCursorPosition;
            pos2.Y--;
            RCOC(
                GetStdHandle(STD_OUTPUT_HANDLE),
                strFromConsoleUp,
                1,
                pos2,
                &dwChars2);
            char c = strFromConsole[0];
            char c2 = strFromConsoleUp[0];
            WORD a = lpAttrib[0];
            if (c2 == '[' || c2 == ']' && dwChars2 != 0)
            {
                    isBlockAbove = 1;
                    newPos = pos;
                    newPos.X--;
            }
            else if(c == '[' || c == ']' && dwChars1 != 0 && a != BLUE && dwAttribs1 != 0)
            {
                    found = 1;
                    newPos = pos;
                    newPos.Y--;
            }
            else {}
	    }
	};
}