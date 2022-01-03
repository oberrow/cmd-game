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
		if (game::Start::ctrlc == true)
			return 0;
		else
			game::Start s{ _getch() };
	}
#endif
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                     

                                                                                                                                       