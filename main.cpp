#include "includes.hpp"
#include "Start.hpp"



int main()
{
#if 0
	int getchRetVal = _getch();
	std::cout << getchRetVal;
	std::cin.get();
#elif 1
	while (true) {
		if (game::GlobalVars::endProg == true)
			return 0;
		else
			game::Start s{ _getch(), "savegame.txt" };
		
	}
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

                                                                                                                                       