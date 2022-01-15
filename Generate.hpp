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
		int filesize(const char* filename)
		{
			// Credits : https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c
			std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
			int size = in.tellg() / 1000000;
			return size;
		}
		void extractIntegerWords(std::string str)
		{
			std::stringstream ss;

			/* Storing the whole string into string stream */
			ss << str;

			/* Running loop till the end of the stream */
			std::string temp;
			SHORT found;
			while (!ss.eof()) {
				int times = 0;
				times++;
				/* extracting word by word from stream */
				ss >> temp;
				std::string num1 = "";
				std::string num2 = "";
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
			int lines = 0;
			std::string line;
			std::ifstream myFile(savegame);
			game::Log l = Log::levelInfoId;
			/*while (std::getline(myFile), line)
				lines++;*/
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
			std::ifstream in_fs;
			in_fs.open(savegame);
			std::string rawContents{};
			std::getline(in_fs, rawContents);
			in_fs.close();
			size_t openingval = rawContents.find('{');
			std::string values{ rawContents };
			size_t closingval = values.find('}');
			if (openingval != std::string::npos && closingval != std::string::npos)
				values = values.substr(openingval, closingval);
			bool is_x = true;
			//////////////////////////////////////////////////////////////////////////////
			// Credits : https://www.geeksforgeeks.org/extract-integers-string-c/
			extractIntegerWords(values);
			/*std::string cpyVals = rawContents;
				x = atoi(cpyVals.c_str() + sizeof("{ ") - 1);
				cpyVals.erase(cpyVals.find("{ " + std::to_string(x)));
				std::cout << cpyVals;
				y = atoi(cpyVals.c_str() + sizeof(", ") - 1);*/
			//////////////////////////////////////////////////////////////////////////////
			newPos = { x, y };
			size_t preComma = values.rfind(',') + 1;
			values.erase(preComma, preComma);
			size_t comma = values.rfind(',');
			std::string block = values.substr(comma);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
			if (block == "REENERY ")
			{
				colorAttributes grass = LIGHTGREEN;
				std::cout << "[] ";
			}
			else if (block == "OCK ")
			{
				colorAttributes color = LIGHTGRAY;
				std::cout << "[] ";
			}
			else if (block == "EDROCK ")
			{
				colorAttributes color = LIGHTBLUE;
				std::cout << "[] ";
			}
			else if (block == "OG ")
			{
				colorAttributes color = BROWN;
				std::cout << "[] ";
			}
			else if (block == "ATER ")
			{
				colorAttributes color = BLUE;
				std::cout << "[] ";
			}
			else
			{
				l.levelError("Generation failed of " + block + " at coordinates X: " + std::to_string(newPos.X) + " Y: " + std::to_string(newPos.Y) + "!");
			}
		}
	};
}
