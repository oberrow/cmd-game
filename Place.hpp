#pragma once
#include "includes.hpp"
#include "colorAttributes.hpp"
#include "movements.hpp"

namespace game {
	class Place {
	public:
		Place(int blockId, CONSOLE_SCREEN_BUFFER_INFO buff) {
			unsigned char space = 32;
			std::cout << space;
			buff.dwCursorPosition.X += 3;
			switch (blockId) {
			case 71:
			{
				colorAttributes color = LIGHTGREEN;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 103:
			{
				colorAttributes color = LIGHTGREEN;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 114:
			{
				colorAttributes color = LIGHTGRAY;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 82:
			{
				colorAttributes color = LIGHTGRAY;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 66:
			{
				colorAttributes color = LIGHTBLUE;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 98:
			{
				colorAttributes color = LIGHTBLUE;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 76:
			{
				colorAttributes color = BROWN;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 108:
			{
				colorAttributes color = BROWN;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 112:
			{
				colorAttributes color = BLUE;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 80:
			{
				colorAttributes color = BLUE;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			//case 122:
			//{
			//	colorAttributes color = BLACK;
			//	const char* buffer = "\b \b \b \b";
			//	buff.dwCursorPosition.X -= 2;

			//	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), buffer, 4, NULL, NULL);
			//	Movements::coordCpy = buff.dwCursorPosition;

			//	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), buff.dwCursorPosition);
			//	break;
			//}
			case 8:
			{
				colorAttributes color = BLACK;
				const char* buffer = "\b \b \b \b";
				buff.dwCursorPosition.X -= 2;
				WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), buffer, 4, NULL, NULL);
				Movements::coordCpy = buff.dwCursorPosition;

				break;
			}
			default:
				break;
		}
		}
	};
}