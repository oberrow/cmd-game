#include "includes.hpp"
#include "Start.hpp"



int main()
{
#if 0
	int getchRetVal = _getch();
	std::cout << getchRetVal;
	std::cin.get();
#elif 0
	CONSOLE_SCREEN_BUFFER_INFO buff;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buff))
	{
		game::Log l{ game::Log::levelInfoId };
		l.levelError("An error has occured. Function GetConsoleScreenBufferInfo() has failed because of an unspecified error");
		_STD terminate();
	_getch();
	}
	while(true)
		game::Movements m(_getch(), buff);
#elif 1
	while (true) {
		if (game::GlobalVars::endProg == true)
			return 0;
		else
			game::Start s{ _getch(), "savegame.txt" };
		
	}
#elif 0
	auto start = std::chrono::high_resolution_clock::now();
	if (game::GlobalVars::endProg == true)
		return 0;
	else
		game::Start s{ _getch(), "savegame.txt" };
	auto end = std::chrono::high_resolution_clock::now();
	auto time = start - end;
	std::cout << "A game tick lasts " << time;
#elif 0
	auto s = std::chrono::high_resolution_clock::now();
	int a = 0;
	do
	{
		a++;
		std::cout << '\n' << a;
	} while (a <= 2499);
	auto e = std::chrono::high_resolution_clock::now();
	auto dur = e - s;
	std::cout << "Took: " << dur;
#endif
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                     

                                                                                                                                       