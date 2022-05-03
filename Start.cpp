#include "GlobalVars.hpp"

#if defined(_WIN64) && STATE && CMDGAME
#include "Start.hpp"

namespace game 
{
	//VOID WINAPI Start::SetConsoleColors(WORD attribs)
	//  {
	//	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	//	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
	//	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	//	GetConsoleScreenBufferInfoEx(hOutput, &cbi);
	//	cbi.wAttributes = attribs;
	//	SetConsoleScreenBufferInfoEx(hOutput, &cbi);
	////}

	std::string Start::GetCurrentBlock()
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
	void Start::save()
	{
		std::string str = savegame;
		str.append("\\savegame.cmdgamesave");
		std::ofstream fstream{ str, std::ios::app };
		//if (getchVal == '\b' && GetCurrentBlock() != "NULL")
		//{
		//	std::string currentBlock = GetCurrentBlock();
		//	std::string possibleFormat = "{ " + std::to_string(in_Buffer.dwCursorPosition.X) + ", " + std::to_string(in_Buffer.dwCursorPosition.Y) + currentBlock + " }, \n";
		//	std::string* fileData = new std::string(read_file(savegame));
		//	if (fileData->contains(possibleFormat))
		//	{
		//		// ------------------------------------------------------
		//		// Credits : http://www.java2s.com/example/cpp/stl/removing-a-substring-from-a-string.html
		//		size_t i = fileData->find(possibleFormat);
		//
		//		if (i != std::string::npos)
		//			fileData->erase(i, possibleFormat.length());
		//		// ------------------------------------------------------
		//		std::ofstream out{ savegame, std::ios::trunc };
		//		out << fileData;
		//		out.close();
		//	}
		//	delete fileData;
		//	return;
		//}
		if (!sStream.empty())
			fstream << sStream << std::flush;
		else
			return;
		fstream.close();
	}
	void Start::start()
	{
		if (times2 == 0)
		{
			setFontSize(18);
		}
		if (times == 1)
		{
			maxConsoleSize = in_Buffer.dwMaximumWindowSize;
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			generate();
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			game::Generate g{ savegame.c_str(), in_Buffer, true };
		}
		dispatch();
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		Colisions* c = nullptr;
		if(use_colisions)
			c = new game::Colisions(in_Buffer);
		if(m_Exp.exp_Gravity)
			game::Gravity g{ in_Buffer.dwCursorPosition, maxConsoleSize };
#define MOVE_TO \
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c->newPos); \
game::Movements::coordCpy = c->newPos
		if (use_colisions)
		{
			if (c->isBlockAbove && !c->isBlockRight && !c->isBlockLeft && !c->found && !isPlacingBlock && !game::GlobalVars::BackSpace)
			{
				MOVE_TO;
			}
			else if (c->found && !c->isBlockRight && !c->isBlockLeft && !c->isBlockAbove && !isPlacingBlock && !game::GlobalVars::BackSpace)
			{
				MOVE_TO;
			}
			else if (!c->found && c->isBlockRight && !c->isBlockLeft && !c->isBlockAbove && !isPlacingBlock && !game::GlobalVars::BackSpace)
			{
				MOVE_TO;
			}
			else if (!c->found && !c->isBlockRight && c->isBlockLeft && !c->isBlockAbove && !isPlacingBlock && !game::GlobalVars::BackSpace)
			{
				MOVE_TO;
			}
			else if (GlobalVars::BackSpace || isPlacingBlock)
			{
				GlobalVars::BackSpace = false;
				isPlacingBlock = false;
			}
		}
		delete c;
	}
	void Start::generate(/*int seed*/)
	{
		times2++;
		if (times == 1)
		{
		COORD newPos = { 1, 9 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
		int divResult = maxConsoleSize.X / 3;
			{
				for (int i = 0; i < divResult; i++)
				{
					colorAttributes grassColor = 0x0A;
					std::cout << "[] ";
					GetConsoleScreenBufferInfo(
						GetStdHandle(STD_OUTPUT_HANDLE),
						&in_Buffer
					);
					/*game::block _block{ "GREENERY", COORD(in_Buffer.dwCursorPosition.X, in_Buffer.dwCursorPosition.Y) };
					GlobalVars::world_map[std::string(std::to_string(in_Buffer.dwCursorPosition.X) + ", " + std::to_string(in_Buffer.dwCursorPosition.Y) + ", GREENERY")] = _block;
				*/
				}
			}
			{
				for (int i = 0; i < divResult * 25; i++)
				{
					colorAttributes stoneColor = colors::lightgray;
					std::cout << "[] ";
					GetConsoleScreenBufferInfo(
						GetStdHandle(STD_OUTPUT_HANDLE),
						&in_Buffer
					);
					/*game::block _block{ "ROCK", COORD(in_Buffer.dwCursorPosition.X, in_Buffer.dwCursorPosition.Y)};
					GlobalVars::world_map[std::string(std::to_string(in_Buffer.dwCursorPosition.X) + ", " + std::to_string(in_Buffer.dwCursorPosition.Y) + ", ROCK")] = _block;
				*/
				}
			}
			{
				for (int i = 0; i < divResult * 3; i++)
				{
					colorAttributes bedrockColor = colors::lightblue;
					std::cout << "[] ";
					GetConsoleScreenBufferInfo(
						GetStdHandle(STD_OUTPUT_HANDLE),
						&in_Buffer
					);
					/*game::block _block{ "BEDROCK", COORD(in_Buffer.dwCursorPosition.X, in_Buffer.dwCursorPosition.Y) };
					GlobalVars::world_map[std::string(std::to_string(in_Buffer.dwCursorPosition.X) + ", " + std::to_string(in_Buffer.dwCursorPosition.Y) + ", BEDROCK")] = _block;
				*/
				}
			}
			newPos.X = 0;
			newPos.Y = 8;
			game::Movements::coordCpy = newPos;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
		}
	}
	void Start::MonitorMemoryUsage()
	{
		// Credits:
		// https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
		// PS. there is some functions / classes that aren't coded by me (or not entirely coded by me)

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		PROCESS_MEMORY_COUNTERS_EX pmc{};
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		game::DeleteLog dl;
		if (physMemUsedByMe >= 3.146e+7)
		{
			dl.~DeleteLog();
#if _MSC_VER >= 1700
			__fastfail(FAST_FAIL_FATAL_APP_EXIT); //If the memory usage is going higher then 30MiB this line will terminate the program
#else 
			std::abort(); //If the memory usage is going higher then 30MiB this line will terminate the program
#endif
		}
	}
	void Start::dispatch()
	{
		if ((char)getchVal == 'b' || (char)getchVal == 'g' || (char)getchVal == 'r' || (char)getchVal == '\b' || (char)getchVal == 'l' || (char)getchVal == 'p' || (char)getchVal == 'B' || (char)getchVal == 'G' || (char)getchVal == 'R' || (char)getchVal == 'L' || (char)getchVal == 'P')
		{
			isPlacingBlock = true;
			Place::Place(getchVal, in_Buffer);
			/*if (!use_old_gen)
			{*/
				if (getchVal == 'g' || getchVal == 'G')
				{
					sStream = { "{ " + std::to_string(in_Buffer.dwCursorPosition.X + 1) + ", " + std::to_string(in_Buffer.dwCursorPosition.Y) + " GREENERY }, \n" };
					save();
				}
				else if (getchVal == 'b' || getchVal == 'B')
				{
					sStream = { "{ " + std::to_string(in_Buffer.dwCursorPosition.X + 1) + ", " + std::to_string(in_Buffer.dwCursorPosition.Y) + " BEDROCK }, \n" };
					save();
				}
				else if (getchVal == 'r' || getchVal == 'R')
				{
					sStream = { "{ " + std::to_string(in_Buffer.dwCursorPosition.X + 1) + ", " + std::to_string(in_Buffer.dwCursorPosition.Y) + " ROCK }, \n" };
					save();
				}
				else if (getchVal == 'p' || getchVal == 'P')
				{
					sStream = { "{ " + std::to_string(in_Buffer.dwCursorPosition.X + 1) + ", " + std::to_string(in_Buffer.dwCursorPosition.Y) + " WATER }, \n" };
					save();
				}
				else if (getchVal == 'l' || getchVal == 'L')
				{
					sStream = { "{ " + std::to_string(in_Buffer.dwCursorPosition.X + 1) + ", " + std::to_string(in_Buffer.dwCursorPosition.Y) + " LOG }, \n" };
					save();
				}
				else if (getchVal == '\b')
				{
					sStream = { "{ " + std::to_string(in_Buffer.dwCursorPosition.X) + ", " + std::to_string(in_Buffer.dwCursorPosition.Y) + " DELETED_BLOCK }, \n" };
					save();
					game::GlobalVars::BackSpace = true;
				}
			//}
		}
		else if ((char)getchVal == 'w' || (char)getchVal == 'a' || (char)getchVal == 's' || (char)getchVal == 'd' || (char)getchVal == (char)32 || (char)getchVal == 'W' || (char)getchVal == 'A' || (char)getchVal == 'S' || (char)getchVal == 'D')
		{
			Movements::Movements(getchVal, in_Buffer);
		}
		else if ((char)getchVal == (char)3)
		{
			ctrlc = true;
		}
	}
	void Start::setFontSize(int FontSize)
	{
		CONSOLE_FONT_INFOEX info = { 0 };
		info.cbSize = sizeof(info);
		info.dwFontSize.Y = FontSize;
		info.FontWeight = FW_BOLD;
		wcscpy_s(info.FaceName, (rsize_t)32, L"Consolas");
		//wcscpy(info.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
	}
}
#endif