#pragma once
#include "includes.hpp"
#include "Place.hpp"
#include "log.hpp"
namespace game {
	class removeFromString {
	public:
		removeFromString(std::string& in, std::string removeFrom) {

			std::string::size_type i = in.find(removeFrom);

			if (i != std::string::npos)
				in.erase(i, removeFrom.length());
		}
		removeFromString() {}
	};
	class Generate
	{
	public:
		Generate(const char* savegame, CONSOLE_SCREEN_BUFFER_INFO buff) {
#if 0
			{
				for (int i = 0; i < 56; i++)
					game::Place::Place(71, savegame, buff);
			}
			{
				for (int i = 0; i < 56 * 25; i++)
					game::Place::Place(114, savegame, buff);
			}
			{
				for (int i = 0; i < 56 * 3; i++)
					game::Place::Place(66, savegame, buff);
			}
#endif
			COORD newPos = { 1, 9 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
			newPos = { 0, 1 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
			std::ifstream in_fs;
			in_fs.open(savegame);
			std::string rawContents{};
			while (std::getline(in_fs, rawContents));
			in_fs.close();
			size_t openingval = rawContents.find('{');
			std::string values{};
			size_t closingval = values.find('}');
			if (openingval != std::string::npos && closingval != std::string::npos)
				values = rawContents.substr(openingval, closingval);
			short x = 0;
			short y = 0;
			bool is_x = true;
			for (int i = 0; i < 1; i++) {
				for (int i = 0; i < values.length(); i++)
				{
					if (isdigit(values[i])) {
						if (is_x == true)
						{
							x = std::atoi((const char*)values[i]);
							removeFromString r{ values, std::to_string(x) };
							is_x = false;
							break;
						}
						else {
							y = std::atoi((const char*)values[i]);
							removeFromString r{ values, std::to_string(y) };
							break;
						}
					}
				}
			}
			game::Log l = Log::levelInfoId;
			newPos = { y, x };
			size_t preComma = values.rfind(',') + 1;
			values.erase(preComma, preComma);
			size_t comma = values.rfind(',');
			std::string block = values.substr(comma);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
			if (block == "GREENERY")
			{
				colorAttributes grass = LIGHTGREEN;
				std::cout << "[] ";
			}
			else if (block == "ROCK")
			{
				colorAttributes color = LIGHTGRAY;
				std::cout << "[] ";
			}
			else if (block == "BEDROCK")
			{
				colorAttributes color = LIGHTBLUE;
				std::cout << "[] ";
			}
			else if (block == "LOG")
			{
				colorAttributes color = BROWN;
				std::cout << "[] ";
			}
			else if (block == "WATER")
			{
				colorAttributes color = BLUE;
				std::cout << "[] ";
			}
			else
				l.levelError("Generation failed at coordinates X: " + std::to_string(newPos.X) + " Y: " + std::to_string(newPos.Y) + "!");
		}
	};
}
