#include "GlobalVars.hpp"
#if defined(_WIN64)
#include "Start.hpp"
#if CMDGAME
#include "includes.hpp"
#else
#include <future>
#include <iostream>
#include <fstream>
#include <thread>
#include <conio.h>
#include <Windows.h>
#include "../util/util.hpp"
#include <vector>
#endif

int attrib = 0;

#if !STATE && !CMDGAME
#endif

#include "Entity.hpp"

#if STATE && CMDGAME
/*
* Parameters:
*	No parameters!
* Return value:
*	game::ExperimentStore
*	to get values do game::ExperimentStore = get_experiments() 
*/
[[nodiscard]] game::ExperimentStore get_experiments() 
{
	game::Config config{ "Experiments.txt" };
	bool data = config.Data[0].boolean_Out;
	return { data };
}
[[nodiscard]] std::tuple<std::string, int, bool, std::string> menu(game::DeleteLog& dl) 
{
	std::string savegame = "";
	game::Store storeOptions1;
	game::Store storeOptions2;
	game::Store storeOptions3;
	game::Config configuration = { game::Config{ "Config.txt" } };
	storeOptions1 = configuration.Data[0];
	storeOptions2 = configuration.Data[1];
	storeOptions3 = configuration.Data[2];
	configuration.Data.pop_back();
	std::string option = std::to_string(storeOptions1.int_Out);
	std::cout << "******************************************************************************************************"
		<< "\n Enter an option 1 to load a savegame or 2 to make a new one, \nPress 3 to delete a savegame, 4 to convert your old savegame to a new one\nand enter def for the default options in the Config.txt file\n Default option is: Option "
		<< option << '\n';
	std::cin >> option;
	
		/*std::cin >> option;
		std::cin.ignore();*/
	if(storeOptions1.str_Out.substr(0, 1)[0] == ' ')
	{
		storeOptions1.str_Out.erase(0, 1);
	}
	if (option == "def" && option.contains("1"))
	{
		return std::tuple(storeOptions1.str_Out, 0x01, storeOptions2.boolean_Out, storeOptions3.str_Out);
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
			return std::tuple(std::string(), 0x00, false, std::string());
		}
		if (!std::filesystem::exists(savegame))
		{
			l.levelError("Hey! " + savegame + " doesn't exist >:(! Did you choose the wrong option?\n", PRINT_ON_DEFAULT_CONSOLE);
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false, std::string());
		}
	}
	else if (option.contains("2"))
	{
		std::cout << "Enter filename to make a new savegame or enter \"end\" (case sensitive) to exit\n";
		std::getline(std::cin, savegame);
		if (savegame == "end")
		{
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false, std::string());
		}
		if (std::filesystem::exists(savegame))
		{
			l.levelError("Hey! " + savegame + " already exists >:( ! Did you choose the wrong option?\n", PRINT_ON_DEFAULT_CONSOLE);
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false, std::string());
		}
		else
		{
			std::filesystem::create_directory(savegame);
			std::ofstream file1{savegame.append("\\savegame.cmdgamesave")};
			std::ofstream file2{savegame.append("\\player.cmdgameplayersave")};
			std::ofstream file3{savegame.append("\\chat.txt")};
			file2 << "{ " << storeOptions3.str_Out << ", op }, \n";
			file1.close();
			file2.close();
			file3.close();
			return std::tuple(savegame, 0x01, storeOptions2.boolean_Out, storeOptions3.str_Out);
		}
	}
	else if (option.contains("3"))
	{
		std::cout << "Enter filename to delete an existing savegame or enter \"end\" (case sensitive) to exit\n";
		std::getline(std::cin, savegame);
		if (savegame == "end")
		{
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false, std::string());
		}
		if (!std::filesystem::exists(savegame))
		{
			l.levelError("Hey! " + savegame + " doesn't exist >:(! Did you choose the wrong option?\n", PRINT_ON_DEFAULT_CONSOLE);
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false, std::string());

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
				return std::tuple(std::string(), 0x00, false, std::string());
			}
			else {
				return std::tuple(std::string(), 0x00, false, std::string());
			}
		}
	}
	else if (option.contains("4"))
	{
		std::string opt = "";
		std::string svgame = "";
		std::cout << "Enter savegame path/filename\n";
		std::cin >> svgame;
		std::cout << "Are you sure you want to convert? Y for yes N for no.\n";
		std::cin >> opt;
		std::string dirn = svgame;
		dirn.erase(dirn.find('.'), dirn.npos);
		if (opt.contains('Y'))
		{
			std::filesystem::create_directory(dirn);
			std::filesystem::copy_file(std::filesystem::current_path().string() + "\\" + svgame, dirn + "\\savegame.cmdgamesave");
			std::ofstream chat{ dirn + "\\chat.txt", std::ios_base::out | std::ios_base::trunc };
			chat.close();
			std::ofstream playerperm{ dirn + "\\player.cmdgameplayersave", std::ios_base::out | std::ios_base::trunc };
			playerperm.close();
			remove(svgame.c_str());
			return std::tuple(dirn, 0x01, storeOptions2.boolean_Out, storeOptions3.str_Out);
		}
		else if (opt.contains('N'))
		{
			std::cout << "Cancelled going to default save";
			return std::tuple(savegame, 0x01, storeOptions2.boolean_Out, storeOptions3.str_Out);
		}
		else
		{
			std::cout << "Un-recognized option!\n";
			return std::tuple("", 0x00, false, "");
		}
	}
	else if (storeOptions1.int_Out == 2 && option == "def")
	{
		if (std::filesystem::exists(savegame))
		{
			l.levelError("Hey! " + savegame + " already exists >:( ! Did you choose the wrong option?\n", PRINT_ON_DEFAULT_CONSOLE);
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false, std::string());
		}
		else
		{
			std::filesystem::create_directory(savegame);
			std::ofstream file1{ savegame.append("\\savegame.cmdgamesave") };
			std::ofstream file2{ savegame.append("\\player.cmdgameplayersave") };
			std::ofstream file3{ savegame.append("\\chat.txt") };
			file2 << "{ " << storeOptions3.str_Out << ", op }, \n";
			file1.close();
			file2.close();
			file3.close();
			return std::tuple(savegame, 0x01, storeOptions2.boolean_Out, storeOptions3.str_Out);
		}
	}
	else if (storeOptions1.int_Out == 3 && option == "def")
	{
		if (savegame == "end")
		{
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false, std::string());
		}
		if (!std::filesystem::exists(savegame))
		{
			l.levelError("Hey! " + savegame + " doesn't exist >:(! Did you choose the wrong option?\n", PRINT_ON_DEFAULT_CONSOLE);
			dl.~DeleteLog();
			return std::tuple(std::string(), 0x00, false, std::string());

		}
		else
		{
			l.levelWarn("Are you sure you want to delete " + savegame + "? Enter Y for yes or N for no\n", PRINT_ON_DEFAULT_CONSOLE);
			std::string choice = "Y";
			std::cin >> choice;
			if (choice == "Y")
			{
				l.levelInfo("Deleting " + savegame + "\n", PRINT_ON_DEFAULT_CONSOLE);
				std::remove(savegame.c_str());
				if (!std::filesystem::exists(savegame))
				{
					l.levelInfo("Deleted " + savegame + " successfully!\n", PRINT_ON_DEFAULT_CONSOLE);
				}
				return std::tuple(std::string(), 0x00, false, std::string());
			}
			else if (choice == "N")
			{
				l.levelInfo("Cancelled!");
				return std::tuple(std::string(), 0x00, false, std::string());
			}
			else {
				return std::tuple(std::string(), 0x00, false, std::string());
			}
		}
	}

	return std::tuple(savegame, 0x01, storeOptions2.boolean_Out, storeOptions3.str_Out);
}
#endif

int main(int argc, char** argv)
{
#if STATE && CMDGAME
	game::DeleteLog dl;
#endif
	/*if (util::IsProcessRunning(L"cmd-game.exe"))
	{
		std::wcout << L"Cmd-game.exe is already running";
		(void)_getch();
		return 1;
	}*/
#if STATE && CMDGAME && !ENTITY_TESTING
	if(!util::IsProcessRunning(L"log.exe")) 
	{
		util::DoAsyncTask([&]()
			{
				ShellExecuteA(
					NULL,
					"open",
					"log.exe",
					NULL,
					NULL,
					SW_MINIMIZE
				);
			});
	}
	SetConsoleTitleA("cmd-game.exe");
	auto [savegame, end, use_colisions, name] = menu(dl);
	auto experments = get_experiments();
	if (end == 0)
	{
		std::cout << "Press any key to continue...";
		(void)_getch();
		OutputDebugStringA("Calling destructor of game::GlobalVars::DeleteLog!\n");
		dl.~DeleteLog();
		OutputDebugStringA("Ending program with code 1 (EXIT_FAILURE)");
		return EXIT_FAILURE;
	}
	else {}
	CONSOLE_SCREEN_BUFFER_INFO csbi_buffer;
	GetConsoleScreenBufferInfo(GetOutputHandle(), &csbi_buffer);
	std::string chatStart = "\"" + savegame + "\" \"";
	if (name.front() == ' ')
		name.erase(0, 1);
	chatStart.append(name);
	chatStart.append("\"");
	std::string str = chatStart;
	util::DoAsyncTask([&]()
		{
			ShellExecuteA(
				NULL,
				"open",
				"chat.exe",
				str.c_str(),
				NULL,
				SW_MINIMIZE
			);
		});
	bool end1 = false;
	std::thread thread{ [&]() {
		std::string str = savegame;
		str.append("\\savegame.cmdgamesave");
		std::string str2 = savegame;
		while (!end1)
		{
			if (/*&game::GlobalVars::world_map != nullptr && */util::CheckFileModification(str, false, 1, false))
			{
				game::Generate g{ str2.c_str(), csbi_buffer, false };
			}
		}
	}
	}; // Lambada
	// basic initalization
	// ------------------------------------

	game::Start s1{ 'S', savegame, use_colisions, experments };
	game::Start s2{ 'w', savegame, use_colisions, experments };
	// ------------------------------------
	WHILETRUE
	{
		int getchVal = _getch();
		// 
 		game::Start s{ getchVal, savegame, use_colisions, get_experiments() };
		if (getchVal == 3 || s.ctrlc)
		{
			OutputDebugStringA("Saving Player position\n");
			std::ofstream file{ savegame.append("\\savegame.cmdgamesave"), std::ios::app };
			std::string tosave = "{ " + std::to_string(game::Movements::coordCpy.X) + ", " + std::to_string(game::Movements::coordCpy.Y) + " PLAYER }, \n";
			file << tosave;
			file.close();
			OutputDebugStringA("Calling destructor of game::GlobalVars::DeleteLog!\n");
			dl.~DeleteLog();
			OutputDebugStringA("Ending thread to check for file modification!\n");
			end1 = true;
			thread.detach();
			OutputDebugStringA("Ending program with code 0 (EXIT_SUCCESS)\n");
			return EXIT_SUCCESS;
			
		}
	}
#else
	{
		SetConsoleTitleA("cmd-game.exe Testing");
		game::entity::Npc basic{ 1, game::entity::npc_types::basic, "=", COORD(9, 1)};
		for (int i = 0; i < 10; i++)
		{
			Sleep(100);
			COORD coord = basic.RandomMoveNPC();
			game::Log l = game::Log::levelInfoId; 
			l.levelInfo(util::CoordToString(coord));
		}
		std::cout 
		<< "Press any key to continue...\n";
		(void)_getch();
	}
#endif
#if 1
	dl.~DeleteLog();
#else
	game::DeleteLog dl;
	dl.~DeleteLog();
#endif
#if !STATE && CMDGAME
	if (thread.joinable())
	{
		end1 = true;
		thread.detach();
	}
#endif
	return 0;
}
#else
#include <iostream>
#include <conio.h>

int main()
{
	std::cout
<< "Only Windows 64 bit is supported!\n"
<< "If you are compiling in x86 architecture on Windows and using msvc (visual studio) compiler you need to compile in x64\n"
<< "Press any key to continue...";
	(void)_getch();
	return 1;
}
#endif