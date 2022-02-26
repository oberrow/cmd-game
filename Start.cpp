#include "Start.hpp"

namespace game 
{
	void Start::save()
	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(50ms);
		std::ofstream fstream{ savegame, std::ios::app };
		if (sStream != "")
			fstream << '\n' << sStream;
		else
			return;
	}
	void Start::start()
	{
		if (times2 == 0)
		{
			setFontSize(18);
			//generate();
		}
		dispatch();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		game::Colisions c = in_Buffer;
#define MOVE_TO \
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c.newPos); \
game::Movements::coordCpy = c.newPos
		if (c.isBlockAbove && !c.found && !isPlacingBlock && !game::GlobalVars::BackSpace)
		{
			MOVE_TO;
		}
		else if (c.found && !c.isBlockAbove && !isPlacingBlock && !game::GlobalVars::BackSpace)
		{
			MOVE_TO;
		}
		isPlacingBlock = true;
	}

	void Start::generate(/*int seed*/)
	{
		times2++;
		COORD newPos = { 1, 9 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
		{
			colorAttributes grassColor = 0x0A;
			for (int i = 0; i < 56; i++)
				std::cout << "[] ";
		}
		{
			colorAttributes stoneColor = 0x07;
			for (int i = 0; i < 56 * 25; i++)
				std::cout << "[] ";
		}
		{
			colorAttributes bedrockColor = 0x09;
			for (int i = 0; i < 56 * 3; i++)
				std::cout << "[] ";
		}
		newPos.X = 1;
		newPos.Y = 9;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
	}
	void Start::MonitorMemoryUsage()
	{
		// Credits:
		// https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
		// PS. there is some functions / classes that aren't coded by me (or not entirely coded by me)

		std::this_thread::sleep_for(std::chrono::milliseconds(3));
		PROCESS_MEMORY_COUNTERS_EX pmc{};
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		if (physMemUsedByMe >= 15000000)
			std::abort(); //If the memory usage is going higher then 15mb this line will terminate the program 
	}
	void Start::dispatch()
	{
		if ((char)getchVal == 'b' || (char)getchVal == 'g' || (char)getchVal == 'r' || (char)getchVal == '\b' || (char)getchVal == 'l' || (char)getchVal == 'p' || (char)getchVal == 'B' || (char)getchVal == 'G' || (char)getchVal == 'R' || (char)getchVal == 'L' || (char)getchVal == 'P')
		{
			isPlacingBlock = true;
			Place::Place(getchVal, in_Buffer, sStream, savegame.c_str());
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
		info.FontWeight = FW_NORMAL;
		wcscpy_s(info.FaceName, (rsize_t)15, L"Consolas");
		//wcscpy(info.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
	}
}
                                                                                                                                                  