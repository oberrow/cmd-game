#include "Start.hpp"
#include "includes.hpp"

#define STATE 1

#pragma warning(disable : 6387)

std::tuple<std::string, int, bool> menu(game::DeleteLog& dl) 
{
	std::string savegame = "";
	game::Store storeOptions1;
	game::Store storeOptions2;
	game::Config configuration = { game::Config{ "Config.txt" } };
	storeOptions1 = configuration.Data[0];
	storeOptions2 = configuration.Data[1];
	std::string option = std::to_string(storeOptions1.int_Out);
	std::cout << "******************************************************************************************************"
		<< "\n Enter an option 1 to load a savegame or 2 to make a new one, \nPress 3 to delete a savegame and enter def for the default options in the Config.txt file\n Default option is: Option "
		<< option << '\n';
	std::getline(std::cin, option);
	
		/*std::cin >> option;
		std::cin.ignore();*/
	if(storeOptions1.str_Out.front() == ' ')
	{
		storeOptions1.str_Out.erase(0, 1);
	}
	if (option == "def" && option.contains("1"))
	{
		return std::tuple(storeOptions1.str_Out, 0x01, storeOptions2.boolean_Out);
	}
	else 
	{
	}
	savegame = storeOptions1.str_Out;
	::game::Log l = game::Log::levelInfoId;
	if (option.contains("1"))
	{
		std::cout << "Enter filename to load existing savegame or enter \"end\" (case sensitive) to exit\n";
		std::getline(std::cin, savegame);
		if (savegame == "end")
		{
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false);
		}
		if (!std::filesystem::exists(savegame))
		{
			l.levelError("Hey! " + savegame + " doesn't exist >:(! Did you choose the wrong option?\n", PRINT_ON_DEFAULT_CONSOLE);
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false);
		}
	}
	else if (option.contains("2"))
	{
		std::cout << "Enter filename to make a new savegame or enter \"end\" (case sensitive) to exit\n";
		std::getline(std::cin, savegame);
		if (savegame == "end")
		{
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false);
		}
		if (std::filesystem::exists(savegame))
		{
			l.levelError("Hey! " + savegame + " already exists >:( ! Did you choose the wrong option?\n", PRINT_ON_DEFAULT_CONSOLE);
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false);
		}
		else
		{
			std::ofstream makeNew{ savegame };
			makeNew.close();
			return std::tuple(savegame, 0x01, storeOptions2.boolean_Out);
		}
	}
	else if (option.contains("3"))
	{
		std::cout << "Enter filename to delete an existing savegame or enter \"end\" (case sensitive) to exit\n";
		std::getline(std::cin, savegame);
		if (savegame == "end")
		{
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false);
		}
		if (!std::filesystem::exists(savegame))
		{
			l.levelError("Hey! " + savegame + " doesn't exist >:(! Did you choose the wrong option?\n", PRINT_ON_DEFAULT_CONSOLE);
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false);

		}
		else
		{
			l.levelWarn("Are you sure you want to delete " + savegame + "? Enter Y for yes or N for no", PRINT_ON_DEFAULT_CONSOLE);
			std::string choice = "Y";
			std::cin >> choice;
			if (choice == "Y")
			{
				l.levelInfo("Deleting " + savegame + "!\n", PRINT_ON_DEFAULT_CONSOLE);
				remove(savegame.c_str());
				return std::tuple(std::string(), 0x00, false);
			}
			else {
				return std::tuple(std::string(), 0x00, false);
			}
		}
	}
	else if (storeOptions1.int_Out == 2 && option.contains("def"))
	{
		if (std::filesystem::exists(savegame))
		{
			l.levelError("Hey! " + savegame + " already exists >:( ! Did you choose the wrong option?\n", PRINT_ON_DEFAULT_CONSOLE);
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false);
		}
		else
		{
			std::ofstream makeNew{ savegame };
			makeNew.close();
			return std::tuple(savegame, 0x01, storeOptions2.boolean_Out);
		}
	}
	else if (storeOptions1.int_Out == 3 && option.contains("def"))
	{
		if (savegame == "end")
		{
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false);
		}
		if (!std::filesystem::exists(savegame))
		{
			l.levelError("Hey! " + savegame + " doesn't exist >:(! Did you choose the wrong option?\n", PRINT_ON_DEFAULT_CONSOLE);
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false);

		}
		else
		{
			l.levelWarn("Are you sure you want to delete " + savegame + "? Enter Y for yes or N for no\n", PRINT_ON_DEFAULT_CONSOLE);
			std::string choice = "Y";
			std::cin >> choice;
			if (choice == "Y")
			{
				l.levelInfo("Deleting " + savegame + "\n", PRINT_ON_DEFAULT_CONSOLE);
				remove(storeOptions1.str_Out.c_str());
				if (!std::filesystem::exists(savegame))
				{
					l.levelInfo("Deleted " + savegame + " successfully!\n", PRINT_ON_DEFAULT_CONSOLE);
				}
				return std::tuple(std::string(), 0x00, false);
			}
			else if (choice == "N")
			{
				l.levelInfo("Cancelled!");
				return std::tuple(std::string(), 0x00, false);
			}
			else {
				return std::tuple(std::string(), 0x00, false);
			}
		}
	}

	return std::tuple(savegame, 0x01, storeOptions2.boolean_Out);
}

int main(int argc, TCHAR** argv)
{
	game::DeleteLog dl;
	//MessageBox(NULL, TEXT("Test"), TEXT("Testing"), MB_ICONERROR);
	// Credits : https://stackoverflow.com/a/14176581/16564788
	//HANDLE mutex = CreateMutexA(0, FALSE, "Local\\$myprogram$"); // try to create a named mutex
	//if (GetLastError() == ERROR_ALREADY_EXISTS) // did the mutex already exist?
	//{
	//	ReleaseMutex(mutex);
	//	return -1; // quit; mutex is released automatically
	//}
#if STATE
	system("start log.exe");
	auto [savegame, end, use_colisions] = menu(dl);
	if (end == 0)
	{
		std::cout << "Press any key to continue...";
		(void)_getch();
		dl.~DeleteLog();
		return 0;
	}
	else {}
	game::Start s1{ 'S', savegame, use_colisions };
	WHILETRUE
	{
		int getchVal = _getch();
		if (getchVal == 3)
		{
			dl.~DeleteLog();
			return 0;
		}
		else
			game::Start s{ getchVal, savegame, use_colisions };
	}
#elif !STATE
	int _gc = _getch();
#endif
	std::ofstream of{ "log.txt", std::ofstream::out | std::ofstream::trunc };
	of << "[END]";
	of.close();
	using namespace std::literals;
	std::this_thread::sleep_for(30ms);
	of.open("log.txt", std::ofstream::out | std::ofstream::trunc);
	of.close();
	return 0;
}