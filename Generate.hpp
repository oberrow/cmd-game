#if defined(_WIN64) && STATE && CMDGAME
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
		int64_t getLines(std::string savegame)
		{
			// Credits : https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file/3482093#3482093
			std::ifstream myfile(savegame);

			// new lines will be skipped unless we stop it from happening:    
			myfile.unsetf(std::ios_base::skipws);

			// count the newlines with an algorithm specialized for counting:
			int64_t line_count = std::count(
				std::istream_iterator<char>(myfile),
				std::istream_iterator<char>(),
				'\n');
			return line_count;
		}
	public:
		Generate(const char* savegame, CONSOLE_SCREEN_BUFFER_INFO buff, bool load_player)
		{
			std::string savegame_stdstring{ savegame };
			std::string savegameToCStr = "\\";
			savegame_stdstring += savegameToCStr += "savegame.cmdgamesave";
			::game::Log l = Log::levelInfoId;
			COORD newPos = { 0, 0 };
			constexpr size_t npos = std::string::npos;
			int64_t lines = getLines(savegame_stdstring);
			std::ifstream in_fs;
			in_fs.open(savegame_stdstring);
			std::string* rawContents{ new std::string };
			if (!std::filesystem::exists(savegame_stdstring))
			{
				l.levelError(std::string(savegame_stdstring) + " doesn't exist! Please make the file first");
				return;
			}
			if (!in_fs.is_open())
			{
				l.levelError("Could not open file " + std::string(savegame_stdstring));
				return;
			}
			else
				l.levelInfo("Succesfully opened " + std::string(savegame_stdstring));
			while (getline(in_fs, *rawContents))
			{
				size_t openingval = rawContents->find('{');
				std::string* values = new std::string{ *rawContents };
				size_t closingval = values->find('}');
				if (openingval != std::string::npos && closingval != std::string::npos)
					*values = values->substr(openingval, closingval - 1);
					{
						// Get Coords
						// ----------------------------------------
						int lastElementInX;
						if (values->find("{ ") != npos)
						{
							x = std::atoi(values->substr(2, 1).c_str());
							lastElementInX = 2;
							if (util::isdigit(values->substr(3, 1).c_str()[0]))
							{
								lastElementInX++;
								std::string s1 = std::to_string(x);
								std::string s2 = std::to_string(std::atoi(values->substr(3, 1).c_str()));
								std::string finalResult1 = s1 + s2;
								x = std::atoi(finalResult1.c_str());
								if (util::isdigit(values->substr(4, 1).c_str()[0]))
								{
									lastElementInX++;
									std::string s1 = std::to_string(x);
									std::string s2 = std::to_string(std::atoi(values->substr(4, 1).c_str()));
									std::string finalResult2 = s1 + s2;
									x = std::atoi(finalResult2.c_str());
								}
							}
						}
						if (values->find("{ " + std::to_string(x) + ", ") != npos)
						{
							if (lastElementInX == 4 || ~lastElementInX > 4)
							{
								y = std::atoi(values->substr(7, 1).c_str());
								if (util::isdigit(values->substr(8, 1).c_str()[0]))
								{
									std::string s1 = std::to_string(y);
									std::string s2 = std::to_string(std::atoi(values->substr(8, 1).c_str()));
									std::string finalResult1 = s1 + s2;
									y = std::atoi(finalResult1.c_str());
								}
							}
							else if(lastElementInX == 3 || ~lastElementInX > 3)
							{
								y = std::atoi(values->substr(6, 1).c_str());
								if (util::isdigit(values->substr(7, 1).c_str()[0]))
								{
									std::string s1 = std::to_string(y);
									std::string s2 = std::to_string(std::atoi(values->substr(7, 1).c_str()));
									std::string finalResult1 = s1 + s2;
									y = std::atoi(finalResult1.c_str());
								}
							}
							else if(lastElementInX == 2 || ~lastElementInX > 2)
							{
								y = std::atoi(values->substr(5, 1).c_str());
								if (util::isdigit(values->substr(6, 1).c_str()[0]))
								{
									std::string s1 = std::to_string(y);
									std::string s2 = std::to_string(std::atoi(values->substr(8, 1).c_str()));
									std::string finalResult1 = s1 + s2;
									y = std::atoi(finalResult1.c_str());
								}
							}
							/*size_t _off = values->find(std::string("{ ").append(std::to_string(x)).append(", "));
							y = std::atoi(values->substr(_off - 1, 1).c_str());
							if (::game::util::isdigit(values->substr(_off, 1).c_str()[0]))
							{
								lastElementInX++;
								std::string s1 = std::to_string(x);
								std::string s2 = std::to_string(std::atoi(values->substr(_off + 1, 1).c_str()));
								std::string finalResult1 = s1 + s2;
								y = std::atoi(finalResult1.c_str());
							}*/
						}
					}
						// ----------------------------------------
					newPos = { x, y };
					if (values->contains("GREENERY"))
					{
						LPCWSTR print = L"[] ";
						WORD color = LIGHTGREEN;
						for (int i = 0; i < 3; i++)
						{
							COORD pos = COORD(newPos.X + i, newPos.Y);
							/*game::block _block{ "GREENERY", COORD(pos) };
							if (&GlobalVars::world_map != nullptr)
								GlobalVars::world_map[std::string(std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", GREENERY")] = _block;
							*/util::OutputAtCoordW(
								GetStdHandle(STD_OUTPUT_HANDLE),
								1,
								&print[i],
								pos,
								color
							);
						}
					}
					else if (values->contains("ROCK"))
					{
						LPCWSTR print = L"[] ";
						WORD color = colors::lightgray;
						for (int i = 0; i < 3; i++)
						{
							COORD pos = COORD(newPos.X + i, newPos.Y);
							/*game::block _block{ "ROCK", COORD(pos) };
							if(&GlobalVars::world_map != nullptr)
								GlobalVars::world_map[std::string(std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", ROCK")] = _block;
							*/util::OutputAtCoordW(
								GetStdHandle(STD_OUTPUT_HANDLE),
								1,
								&print[i],
								pos,
								color
							);
						}
					}
					else if (values->contains("BEDROCK"))
					{
						LPCWSTR print = L"[] ";
						WORD color = LIGHTBLUE;
						for (int i = 0; i < 3; i++)
						{
							COORD pos = COORD(newPos.X + i, newPos.Y);
							/*game::block _block{ "BEDROCK", COORD(pos) };
							if (&GlobalVars::world_map != nullptr)
								GlobalVars::world_map[std::string(std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", BEDROCK")] = _block;
							*/util::OutputAtCoordW(
								GetStdHandle(STD_OUTPUT_HANDLE),
								1,
								&print[i],
								pos,
								color
							);
						}
					}
					else if (values->contains("LOG"))
					{
						LPCWSTR print = L"[] ";
						WORD color = BROWN;
						for (int i = 0; i < 3; i++)
						{
							COORD pos = COORD(newPos.X + i, newPos.Y);
							/*game::block _block{ "LOG", COORD(pos) };
							if (&GlobalVars::world_map != nullptr)
								GlobalVars::world_map[std::string(std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", LOG")] = _block;
							*/util::OutputAtCoordW(
								GetStdHandle(STD_OUTPUT_HANDLE),
								1,
								&print[i],
								pos,
								color
							);
						}
					}
					else if (values->contains("WATER"))
					{
						LPCWSTR print = L"[] ";
						WORD color = BLUE;
						for (int i = 0; i < 3; i++)
						{
							COORD pos = COORD(newPos.X + i, newPos.Y);
							/*game::block _block{ "WATER", COORD(pos) };
							if (&GlobalVars::world_map != nullptr)
								GlobalVars::world_map[std::string(std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", WATER")] = _block;
							*/util::OutputAtCoordW(
								GetStdHandle(STD_OUTPUT_HANDLE),
								1,
								&print[i],
								pos,
								color
							);
						}
					}
					else if (values->contains("DELETED_BLOCK"))
					{
						LPCSTR toPrint = "  ";
						/*if(&GlobalVars::world_map != nullptr)
							GlobalVars::world_map.erase(std::string(std::to_string(buff.dwCursorPosition.X) + ", " + std::to_string(buff.dwCursorPosition.Y) + ", WATER"));
						*/for (int i = 0; i < 3; i++)
						{
							util::OutputAtCoordA(
								GetStdHandle(STD_OUTPUT_HANDLE),
								1,
								&toPrint[i],
								COORD(newPos.X + i, newPos.Y),
								LIGHTGRAY
							);
						}
					}
					else if (values->contains("PLAYER") && load_player) 
					{
						SetConsoleCursorPosition
						(
							GetOutputHandle(),
							newPos
						);
						game::Movements::coordCpy = newPos;
					}
					else
					{
						if(!values->empty())
							l.levelError("Error GEN01! Unrecognized block! Current coordinates are X: " + std::to_string(newPos.X) + " Y: " + std::to_string(newPos.Y) + "!");
					}
					delete values;
			}
			delete rawContents;
			in_fs.close();
		}
	};
}
#endif