#pragma once
#include "includes.h"
#include "colorAttributes.h"
#include "movements.h"

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
				colorAttributes color = 0x0A;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 103:
			{
				colorAttributes color = 0x0A;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 114:
			{
				colorAttributes color = 0x07;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 82:
			{
				colorAttributes color = 0x07;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 66:
			{
				colorAttributes color = 0x09;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 98:
			{
				colorAttributes color = 0x09;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 124:
			{
				colorAttributes color = 0x06;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 108:
			{
				colorAttributes color = 0x06;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 112:
			{
				colorAttributes color = 0x01;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 80:
			{
				colorAttributes color = 0x01;
				std::cout << "[]";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 122:
			{
				colorAttributes color = 0x00;
				const char* buffer = "\b \b \b \b";
				buff.dwCursorPosition.X -= 2;

				WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), buffer, 4, NULL, NULL);
				Movements::coordCpy = buff.dwCursorPosition;

				//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), buff.dwCursorPosition);
				break;
			}
			case 90:
			{
				colorAttributes color = 0x00;
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
