#include "Start.hpp"
#include "includes.hpp"

#define STATE 1

int main(int argc, TCHAR** argv)
{
	game::DeleteLog l;
	//MessageBox(NULL, TEXT("Test"), TEXT("Testing"), MB_ICONERROR);
#if STATE
	system("start log.exe");
	WHILETRUE
	{
		if (game::Start::ctrlc == true)
			return 0;
		else
			game::Start s{ _getch(), "savegame.txt" };
	}
#elif !STATE
	std::ostream& cout = std::cout;
	cout << "Does this work c++?";
#endif
	std::ofstream of{ "log.txt", std::ofstream::out | std::ofstream::trunc };
	of << "[END]";
	of.close();
	using namespace std::literals;
	std::this_thread::sleep_for(105ms);
	std::ofstream of2{ "log.txt", std::ofstream::out | std::ofstream::trunc };
	of2.close();
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                     