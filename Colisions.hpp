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
        TCHAR strFromConsoleRight[1];
        TCHAR strFromConsoleLeft[1];
        //WORD lpAttrib;
	public:
        COORD newPos{};
        bool found = false;
        bool isBlockAbove = false;
        bool isBlockRight = false;
        bool isBlockLeft = false;
		Colisions(CONSOLE_SCREEN_BUFFER_INFO buff)
		{
#define RCOA ReadConsoleOutputAttribute
#define RCOC ReadConsoleOutputCharacterW
            COORD pos = buff.dwCursorPosition;
            DWORD dwChars1;
            DWORD dwChars2;
            DWORD dwChars3;
            DWORD dwChars4;
            RCOC(
                GetStdHandle(STD_OUTPUT_HANDLE),
                strFromConsole,
                1,
                pos,
                &dwChars1);
            COORD pos2 = buff.dwCursorPosition;
            pos2.Y--;
            RCOC(
                GetStdHandle(STD_OUTPUT_HANDLE),
                strFromConsoleUp,
                1,
                pos2,
                &dwChars2);
            COORD pos3 = buff.dwCursorPosition;
            pos3.X++;
            RCOC(
                GetStdHandle(STD_OUTPUT_HANDLE),
                strFromConsoleRight,
                1,
                pos3,
                &dwChars3);
            COORD pos4 = buff.dwCursorPosition;
            pos4.X--;
            RCOC(
                GetStdHandle(STD_OUTPUT_HANDLE),
                strFromConsoleLeft,
                1,
                pos4,
                &dwChars4);
            char c = strFromConsole[0];
            char c2 = strFromConsoleUp[0];
            char c3 = strFromConsoleRight[0];
            char c4 = strFromConsoleLeft[0];
            if (c2 == '[' || c2 == ']' && dwChars2 != 0)
            {
                isBlockAbove = 1;
                newPos = pos;
                newPos.X--;
            }
            else if(c == '[' || c == ']' && dwChars1 != 0)
            {
                found = 1;
                newPos = pos;
                newPos.Y--;
            }
            else if(c3 == '[' || c3 == ']' && dwChars3 != 0)
            {
                isBlockRight = 1;
                newPos = pos;
                newPos.X--;
            }
            else if(c4 == '[' || c4 == ']' && dwChars4 != 0)
            {
                isBlockLeft = 1;
                newPos = pos;
                newPos.X++;
            }
            else {}
	    }
	};
}