#pragma once
#include "includes.hpp"
#include "log.hpp"
#include "movements.hpp"

namespace game {
	class Colisions
	{
    private:
		Log l{ Log::levelInfoId };
        TCHAR strFromConsole[1];
	public:
        bool found = false;
		Colisions(CONSOLE_SCREEN_BUFFER_INFO buff)
		{
            COORD pos = buff.dwCursorPosition;
            DWORD dwChars;
            ReadConsoleOutputCharacter(
                GetStdHandle(STD_OUTPUT_HANDLE),
                strFromConsole,
                1,
                pos,
                &dwChars);
            char c = strFromConsole[0];
            COORD newPos = pos;
            newPos.Y--;
            if (c == '[' || c == ']' && dwChars != 0 && game::GlobalVars::BackSpace != true)
            {
                found = 1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
                Movements::coordCpy = newPos;
            }
            else
            {}
	    }
	};
}