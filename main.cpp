#include "includes.hpp"
#include "Start.hpp"

int main()
{
#if 0
	int getchRetVal = _getch();
	std::cout << getchRetVal;
	std::cin.get();
#elif 0
	while (true) {
		if (game::GlobalVars::endProg == true)
			return 0;
		else
			game::Start s{ _getch(), "savegame.txt" };
	}
#endif

	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                     