#pragma once
#include "includes.hpp"
#include "colorAttributes.hpp"
#include "movements.hpp"
#include "log.hpp"

namespace game {
	class Place {
	private:
		Log l = Log::levelInfoId;
	public:
		Place(int blockId, CONSOLE_SCREEN_BUFFER_INFO buff, std::ostream& outFile, const char* savegame) {
			unsigned char space = 32;
			std::cout << space;
			buff.dwCursorPosition.X += 3;
			if (!std::filesystem::exists(std::string(savegame)))
			{
				std::ofstream f{ savegame, std::ios::trunc };
			}
			switch (blockId) {
			case 71:
			{
				{
					colorAttributes color = LIGHTGREEN;
					std::cout << "[]";
				}
				outFile << "\n{ " + std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", GREENERY }, ";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 103:
			{
				{
					colorAttributes color = LIGHTGREEN;
					std::cout << "[]";
				}
				outFile << "\n{ " + std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", GREENERY }, ";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 114:
			{
				{
					colorAttributes color = LIGHTGRAY;
					std::cout << "[]";
				}
				outFile << "\n{ " + std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", ROCK }, ";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 82:
			{
				{
					colorAttributes color = LIGHTGRAY;
					std::cout << "[]";
				}
				outFile << "\n{ " + std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", ROCK }, ";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 66:
			{
				{
					colorAttributes color = LIGHTBLUE;
					std::cout << "[]";
				}
				outFile << "\n{ " + std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", BEDROCK }, ";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 98:
			{
				{
					colorAttributes color = LIGHTBLUE;
					std::cout << "[]";
				}
				outFile << "\n{ " + std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", BEDROCK }, ";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 76:
			{
				{
					colorAttributes color = BROWN;
					std::cout << "[]";
				}
				outFile << "\n{ " + std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", LOG }, ";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 108:
			{
				{
					colorAttributes color = BROWN;
					std::cout << "[]";
				}
				outFile << "\n{ " + std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", LOG }, ";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 112:
			{
				{
					colorAttributes color = BLUE;
					std::cout << "[]";
				}
				outFile << "\n{ " + std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", WATER }, ";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
			case 80:
			{
				{
					colorAttributes color = BLUE;
					std::cout << "[]";
				}
				outFile << "\n{ " + std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", WATER }, ";
				Movements::coordCpy = buff.dwCursorPosition;
				break;
			}
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