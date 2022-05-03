#if defined(_WIN64) && STATE && CMDGAME
#pragma once
#include "includes.hpp"
#include "log.hpp"

namespace game {
	class Colisions
	{
    private:
        std::string GetCurrentBlock()
        {
            WORD lpAttrib = 0;
            DWORD dwAttribs1;
            BOOL rcoa = ReadConsoleOutputAttribute(
                GetStdHandle(STD_OUTPUT_HANDLE),
                &lpAttrib,
                1,
                game::Movements::coordCpy,
                &dwAttribs1
            );
            if (dwAttribs1 == 0)
            {
                return "NULL";
            }
            else
            {
                if (lpAttrib == LIGHTGREEN)
                {
                    return "GRENNERY";
                }
                else if (lpAttrib == LIGHTBLUE)
                {
                    return "BEDROCK";
                }
                else if (lpAttrib == BLUE)
                {
                    return "WATER";
                }
                else if (lpAttrib == colors::darkgray)
                {
                    return "ROCK";
                }
                else if (lpAttrib == BROWN)
                {
                    return "LOG";
                }
                else
                {
                    return "NULL";
                }
            }
        }
		Log l{ Log::levelInfoId };
        TCHAR strFromConsole[1];
        TCHAR strFromConsoleUp[1];
        TCHAR strFromConsoleRight[1];
        TCHAR strFromConsoleLeft[1];
        TCHAR strFromConsoleDown[1];
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
            TCHAR c = strFromConsole[0];
            TCHAR c2 = strFromConsoleUp[0];
            TCHAR c3 = strFromConsoleRight[0];
            TCHAR c4 = strFromConsoleLeft[0];
            std::string key = std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", WATER";
            //game::block* tmp{};
            //game::block water{};
            //if (GlobalVars::world_map.contains(key))
            //{
            //    tmp = new block(GlobalVars::world_map.at(key));
            //}
            //water = *tmp;
            //delete tmp;
            if (c2 == '[' || c2 == ']' && dwChars2 != 0)
            {
                isBlockAbove = 1;
                newPos = pos;
                newPos.X--;
            }
            else if(c == L'[' || c == L']' && dwChars1 != 0)
            {
                found = 1;
                newPos = pos;
                newPos.Y--;
            }
            else if(c3 == L'[' || c3 == L']' && dwChars3 != 0)
            {
                isBlockRight = 1;
                newPos = pos;
                newPos.X--;
            }
            else if(c4 == L'[' || c4 == L']' && dwChars4 != 0)
            {
                isBlockLeft = 1;
                newPos = pos;
                newPos.X++;
            }
            else {}
	    }
	};
}
#endif