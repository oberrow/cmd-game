#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include "../cmd-game/colorAttributes.hpp"

#define WHILETRUE while(true)

using namespace std::chrono_literals;

int main(int argc, char** argv)
{
	WHILETRUE{
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
			return 0;
		}
		else {}
		sub = "";
	}
		str = "";
	std::this_thread::sleep_for(100ms);
	system("cls");
	}
}
