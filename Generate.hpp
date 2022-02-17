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
	private:
		SHORT x = 0, y = 0;
		const char* savegame;
		int getLines()
		{
			// Credits : https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file/3482093#3482093
			std::ifstream myfile(savegame);

			// new lines will be skipped unless we stop it from happening:    
			myfile.unsetf(std::ios_base::skipws);

			// count the newlines with an algorithm specialized for counting:
			unsigned line_count = std::count(
				std::istream_iterator<char>(myfile),
				std::istream_iterator<char>(),
				'\n');
			return line_count;
		}
	public:
		Generate(const char* savegame, CONSOLE_SCREEN_BUFFER_INFO buff)
			:savegame(savegame)
		{
			game::Log l = Log::levelInfoId;
			COORD newPos = { 1, 9 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
			newPos = { 0, 1 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
			constexpr size_t npos = std::string::npos;
			int lines = getLines();
			std::ifstream in_fs;
			in_fs.open(savegame);
			std::string* rawContents{ new std::string };
			if (!in_fs.is_open())
				l.levelError("Could not open file " + std::string(savegame));
			else
				l.levelInfo("Succesfully opened " + std::string(savegame));
			while(getline(in_fs, *rawContents))
			{
				size_t openingval = rawContents->find('{');
				std::string* values = new std::string{ *rawContents };
				size_t closingval = values->find('}');
				if (openingval != std::string::npos && closingval != std::string::npos)
					*values = values->substr(openingval, closingval);
				{
					// Get Coords
					// ----------------------------------------
					if (values->find("{ ") != npos)
					{
						x = std::atoi(values->substr(2, 2).c_str());
						if (std::isdigit(std::atoi(values->substr(3, 3).c_str())))
						{
							std::string s1 = std::to_string(x);
							std::string s2 = std::to_string(std::atoi(values->substr(3, 3).c_str()));
							std::string finalResult = s1 + s2;
							x = std::atoi(finalResult.c_str());
							if (std::isdigit(std::atoi(values->substr(4, 4).c_str())))
							{
								std::string s1 = std::to_string(x);
								std::string s2 = std::to_string(std::atoi(values->substr(4, 4).c_str()));
								std::string finalResult = s1 + s2;
								x = std::atoi(finalResult.c_str());
							}
						}
					}
					if (values->find("{ " + std::to_string(x) + ", ") != npos)
					{
						y = std::atoi(values->substr(5, 5).c_str());
						if (std::isdigit(std::atoi(values->substr(6, 6).c_str())))
						{
							std::string s1 = std::to_string(y);
							std::string s2 = std::to_string(std::atoi(values->substr(6, 6).c_str()));
							std::string finalResult = s1 + s2;
							y = std::atoi(finalResult.c_str());
						}
					}
					// ----------------------------------------
				}
				newPos = { x, y };
				size_t preComma = values->rfind(',') + 1;
				values->erase(preComma, preComma);
				size_t comma = values->rfind(',');
				std::string block;
				if(!values->empty())
					block = values->substr(comma, std::string::npos);
				else {

				}
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
				if (block == ",REENERY ")
				{
					colorAttributes grass = LIGHTGREEN;
					std::cout << "[] ";
				}
				else if (block == ",OCK ")
				{
					colorAttributes color = LIGHTGRAY;
					std::cout << "[] ";
				}
				else if (block == ",EDROCK ")
				{
					colorAttributes color = LIGHTBLUE;
					std::cout << "[] ";
				}
				else if (block == ",OG ")
				{
					colorAttributes color = BROWN;
					std::cout << "[] ";
				}
				else if (block == ",ATER ")
				{
					colorAttributes color = BLUE;
					std::cout << "[] ";
				}
				else if (block == ",ULL")
				{
					l.levelInfo("NULL block detected! Debug only!");
				}
				else
				{
					l.levelError("Generation failed of " + block + " at coordinates X: " + std::to_string(newPos.X) + " Y: " + std::to_string(newPos.Y) + "!");
				}
			}
			in_fs.close();
		}
	};
}
