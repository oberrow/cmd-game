#include "../util/util.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <filesystem>

int main(int argc, char** argv)
{
	bool yesno = true;
	do
	{
		std::string world_name = "My World";
		if (argc > 1)
			world_name = argv[1];
		// Actual message
		const char* rec = "}v{uk";
		// Return Value of recv
		int ec{};
		// Message to send back
		const char* send = "";
		util::InternetServerTDP inetS{ 100 };
		std::cout << "Checking for connection requests!\n";
		inetS.AcceptConnectionFromClient();
		std::cout << "Accepted connection request\n";
		do {
			std::cout << "Checking for messages from client!\n";
			ec = inetS.ReciveMessageFromClient();
			std::cout << "Recived message!\n"
				<< "Extracting message from message buffer\n";
			rec = inetS.GetMessageFromBuffer();
			std::cout
				<< "Extracted message!\n Message is \n"
				<< rec;
			if (_stricmp(rec, "GAME_PROTOCOL_GET 0x00\r\n\r\n") == 0 || _stricmp(rec, "GAME_PROTOCOL_GET 0x00") == 0)
			{
				inetS.SendMessageToClient(world_name.c_str());
			}
			else if (_stricmp(rec, "GAME_PROTOCOL_GET 0x01\r\n\r\n") == 0 || _stricmp(rec, "GAME_PROTOCOL_GET 0x01") == 0)
			{
				std::string ln = "";
				std::ifstream ifstr;
				std::ifstream ifstr2;
				if (std::filesystem::exists(std::filesystem::current_path().string() + "\\" + world_name))
				{
					ifstr.open(std::filesystem::current_path().string() + "\\" + world_name + "\\savegame.cmdgamesave");
					ifstr2.open(std::filesystem::current_path().string() + "\\" + world_name + "\\savegame.cmdgamesave");
				}
				else return 1;

				ifstr2.unsetf(std::ios_base::skipws);

				int64_t line_count = std::count(
					std::istream_iterator<char>(ifstr2),
					std::istream_iterator<char>(),
					'\n');
				std::stringstream lncount{};
				lncount << "Line Count in savegame [" << line_count << ']';
				inetS.SendMessageToClient(lncount.str().c_str());
				std::cout << "\nSending " << line_count << " lines of the savegame to client\n";
				while (std::getline(ifstr, ln))
				{
					ln = ln.append("\n");
					inetS.SendMessageToClient(ln.c_str());
				}
			}
			else if (_stricmp(rec, "GAME_PROTOCOL_GET 0x02\r\n\r\n") == 0 || _stricmp(rec, "GAME_PROTOCOL_GET 0x02") == 0)
			{
				std::string ln = "";
				std::ifstream ifstr;
				std::ifstream ifstr2;
				if (std::filesystem::exists(std::filesystem::current_path().string() + "\\" + world_name))
				{
					ifstr.open(std::filesystem::current_path().string() + "\\" + world_name + "\\chat.txt");
					ifstr2.open(std::filesystem::current_path().string() + "\\" + world_name + "\\chat.txt");
				}
				else return 1;

				ifstr2.unsetf(std::ios_base::skipws);

				int64_t line_count = std::count(
					std::istream_iterator<char>(ifstr2),
					std::istream_iterator<char>(),
					'\n');
				std::stringstream lncount{};
				lncount << "Line Count in chat file [" << line_count << ']';
				inetS.SendMessageToClient(lncount.str().c_str());
				std::cout << "\nSending " << line_count << " lines of the chat to client\n";
				while (std::getline(ifstr, ln))
				{
					ln = ln.append("\n");
					inetS.SendMessageToClient(ln.c_str());
				}
			}
			else
			{
				std::cout << "\nGAME_PROTOCOL_ERR 0x00 Invalid Request!\n";
				inetS.SendMessageToClient("GAME_PROTOCOL_ERR 0x00 Invalid Request!");
				inetS.CloseSocket();
				break;
			}
		} while (ec > 0);
		std::cout << "Closing connection!\n";
		inetS.CloseSocket();
		std::cout << "Closed connection!\n"
			<< "Would you like to restart? Y for yes N for no\n";
		std::string yn = "N";
		std::cin >> yn;
		if (_stricmp(yn.c_str(), "Y") == 0)
		{}
		else if (_stricmp(yn.c_str(), "N") == 0)
		{
			yesno = false;
			std::cout << "\nPress any key to continue...";
		}
	} while (yesno);
	(void)_getch();
}