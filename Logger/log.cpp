#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <filesystem>
#include "../cmd-game/colorAttributes.hpp"
#include "../util/util.hpp"

#define WHILETRUE while(true)

using namespace std::chrono_literals;

int main(int argc, char** argv)
{
	util::RunOnDestruction RoD([&](void)
		{ 
			std::ofstream of;
			of.open("log.txt", std::ofstream::out | std::ofstream::trunc);
			of.close();
		}); // Lambada
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		std::string str = "";
		std::ifstream is{};
		if (!std::filesystem::exists("log.txt")) return ERROR_FILE_NOT_FOUND;
		else is.open("log.txt");
		if (!is.is_open()) return 1;
		while (std::getline(is, str))
		{
			size_t pos1 = str.find('[') + 1;
			size_t pos2 = str.find(']') - 1;
			std::string sub = str.substr(pos1, pos2);
			if (sub == "INFO")
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				std::cout << str << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			else if (sub == "WARNING")
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				std::cout << str << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			else if (sub == "ERROR")
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << str << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
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
		util::clear();
	}
}
