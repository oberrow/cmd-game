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
		void extractIntegerWords(std::string str)
		{
			std::stringstream ss;

			/* Storing the whole string into string stream */
			ss << str;

			/* Running loop till the end of the stream */
			std::string temp;
			int found;
			while (!ss.eof()) {

				/* extracting word by word from stream */
				ss >> temp;

				/* Checking the given word is integer or not */
				if (std::stringstream(temp) >> found)
				{
					x = found;
					y = found;
				}

				/* To save from space at the end of string */
				temp = "";
			}
		}
	public:
		Generate(const char* savegame, CONSOLE_SCREEN_BUFFER_INFO buff)
			:savegame(savegame)
		{
			game::Log l = Log::levelInfoId;
			//			{
			//				for (int i = 0; i < 56; i++)
			//					game::Place::Place(71, savegame, buff);
			//			}
			//			{
			//				for (int i = 0; i < 56 * 25; i++)
			//					game::Place::Place(114, savegame, buff);
			//			}
			//			{
			//				for (int i = 0; i < 56 * 3; i++)
			//					game::Place::Place(66, savegame, buff);
			//			}
			COORD newPos = { 1, 9 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
			newPos = { 0, 1 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
			constexpr size_t npos = std::string::npos;
			int lines = getLines();
			for (int i = 1; i < lines; i++)
			{
				l.levelInfo(std::format("Generating! Please wait... Line : {}", i, "\n\n"));
				std::ifstream in_fs;
				in_fs.open(savegame);
				std::string* rawContents{ new std::string };
				for(int nested = 1; nested < i; nested++)
					in_fs.ignore(npos, '\n');
				std::getline(in_fs, *rawContents);
				in_fs.close();
				size_t openingval = rawContents->find('{');
				std::string* values = new std::string{ *rawContents };
				size_t closingval = values->find('}');
				if (openingval != std::string::npos && closingval != std::string::npos)
					*values = values->substr(openingval, closingval);
				extractIntegerWords(*values);
				// Credits : TheCherno Discord server
				/*std::string cpyVals = rawContents;
					x = atoi(cpyVals.c_str() + sizeof("{ ") - 1);
					cpyVals.erase(cpyVals.find("{ " + std::to_string(x)));
					std::cout << cpyVals;
					y = atoi(cpyVals.c_str() + sizeof(", ") - 1);*/
				newPos = { x, y };
				size_t preComma = values->rfind(',') + 1;
				values->erase(preComma, preComma);
				size_t comma = values->rfind(',');
				std::string* block = new std::string;
				try {
					if(rawContents->find("//") != npos)
						*block = values->substr(comma, std::string::npos);
				}
				catch (std::out_of_range)
				
				{
					delete block;
					game::GameInterrupt("An exception has happened at line 109 in the file \"Generate.hpp\"! Exception code : \"std::out_of_range\"");
				}
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
				if (*block == "REENERY ")
				{
					colorAttributes grass = LIGHTGREEN;
					std::cout << "[] ";
				}
				else if (*block == "OCK ")
				{
					colorAttributes color = LIGHTGRAY;
					std::cout << "[] ";
				}
				else if (*block == "EDROCK ")
				{
					colorAttributes color = LIGHTBLUE;
					std::cout << "[] ";
				}
				else if (*block == "OG ")
				{
					colorAttributes color = BROWN;
					std::cout << "[] ";
				}
				else if (*block == "ATER ")
				{
					colorAttributes color = BLUE;
					std::cout << "[] ";
				}
				else if (*block == "ULL")
					return;
				else
				{
					l.levelError("Generation failed of " + *block + " at coordinates X: " + std::to_string(newPos.X) + " Y: " + std::to_string(newPos.Y) + "!");
				}
				delete block;
			}
		}
	};
}
