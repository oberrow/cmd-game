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
		int getchVal = _getch();
		if (getchVal == 3)
			return 0;
		else
			game::Start s{ getchVal, "savegame.txt" };
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