#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include "../cmd-game/colorAttributes.hpp"
#include "../util/util.hpp"

#define WHILETRUE while(true)

using namespace std::chrono_literals;

int main(int argc, char** argv)
{
	util::RunOnDestruction RoD([](void)
		{ 
			std::ofstream of;
			of.open("log.txt", std::ofstream::out | std::ofstream::trunc);
			of.close();
		}); // Lambada
	HANDLE mutex = CreateMutexA(0, FALSE, "Local\\$myprogram$"); // try to create a named mutex
	if (GetLastError() == ERROR_ALREADY_EXISTS) // did the mutex already exist?
	{
		ReleaseMutex(mutex);
		return -1; // quit; mutex is released automatically
	}
	WHILETRUE
	{
	std::string str = "";
	std::ifstream is{ "log.txt" };
	while (std::getline(is, str))
	{
		size_t pos1 = str.find('[') + 1;
		size_t pos2 = str.find(']') - 1;
		std::string sub = str.substr(pos1, pos2);
		if (sub == "INFO")
		{
			game::colorAttributes color = GREEN;
			std::cout << str << std::endl;
		}
		else if (sub == "WARNING")
		{
			game::colorAttributes color = YELLOW;
			std::cout << str << std::endl;
		}
		else if (sub == "ERROR")
		{
			game::colorAttributes color = FOREGROUND_RED | FOREGROUND_INTENSITY;
			std::cout << str << std::endl;
		}
		else if (sub == "END")
		{
			std::cout << "Ending program! Please wait...\n";
			RoD.~RunOnDestruction();
			return 0;
		}
		else {}
		sub = "";
	}
		str = "";
	std::this_thread::sleep_for(25ms);
	system("cls");
	}
}
