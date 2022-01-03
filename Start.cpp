#include "Start.h"

namespace game 
{
	void Start::start()
	{
		if (times2 == 0)
		{
			setFontSize(18);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			generate();
		}
#if 1
		Colisions c = in_Buffer;
#endif
			dispatch();
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
		newPos = { 0, 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
	}
	void Start::MonitorMemoryUsage()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(3));
		PROCESS_MEMORY_COUNTERS_EX pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		if (physMemUsedByMe >= 15000000)
			_STD terminate(); //If the memory usage is going higher then 100mb this line will terminate the program 
	}
	void Start::dispatch()
	{
		if ((char)getchVal == 'b' || (char)getchVal == 'g' || (char)getchVal == 'r' || (char)getchVal == 'z' || (char)getchVal == 'l' || (char)getchVal == 'p' || (char)getchVal == 'B' || (char)getchVal == 'G' || (char)getchVal == 'R' || (char)getchVal == 'Z' || (char)getchVal == 'L' || (char)getchVal == 'P')
			Place::Place(getchVal, in_Buffer);
		else if ((char)getchVal == 'w' || (char)getchVal == 'a' || (char)getchVal == 's' || (char)getchVal == 'd' || (char)getchVal == (char)32 || (char)getchVal == 'W' || (char)getchVal == 'A' || (char)getchVal == 'S' || (char)getchVal == 'D')
			Movements::Movements(getchVal, in_Buffer);
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
                                                                                                                                                  