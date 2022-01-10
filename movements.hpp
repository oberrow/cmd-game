#pragma once
#include "includes.hpp"
#define OUT_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)
namespace game {
	class Movements {
	private:
		inline static int returnVal;
		inline static CONSOLE_SCREEN_BUFFER_INFO m_scr_buffer{};
		inline static COORD coordCpy = m_scr_buffer.dwCursorPosition;
	public:
		Movements(int key, CONSOLE_SCREEN_BUFFER_INFO buff)
		{
			m_scr_buffer = buff;
			switch (key)
			{
			case 119:
			{
				//w key (lowercase)
				int currentCoordY = coordCpy.Y;
				coordCpy.Y--;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.Y == currentCoordY)
					coordCpy.Y--;
				break;
			}
			case 87:
			{
				//W key (Uppercase)
				int currentCoordY = coordCpy.Y;
				coordCpy.Y--;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.Y == currentCoordY)
					coordCpy.Y--;
				break;
			}
			case 115:
			{
				//s key (lowercase)
				int currentCoordY = coordCpy.Y;
				coordCpy.Y++;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.Y == currentCoordY)
					coordCpy.Y++;;
				break;
			}
			case 83:
			{
				//S key (Uppercase)
				int currentCoordY = coordCpy.Y;
				coordCpy.Y++;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.Y == currentCoordY)
					coordCpy.Y++;
				break;
			}
			case 97:
			{
				//a key (lowercase)
				int currentCoordX = coordCpy.X;
				coordCpy.X--;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.X == currentCoordX)
					coordCpy.X--;
				break;
			}
			case 65:
			{
				//A key (Uppercase)
				int currentCoordX = coordCpy.X;
				coordCpy.X--;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.X == currentCoordX)
					coordCpy.X--;
				break;
			}
			case 100:
			{
				//d key (lowercase)
				int currentCoordX = coordCpy.X;
				coordCpy.X++;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.X == currentCoordX)
					coordCpy.X++;
				break;
			}
			case 68:
			{
				//D key (Uppercase)
				int currentCoordX = coordCpy.X;
				coordCpy.X++;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.X == currentCoordX)
					coordCpy.X++;
				break;
			}
			case 32:
			{
				//Space key

				coordCpy.Y--;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				coordCpy.Y++;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);

			}
			default:
				break;
			}
		}
		friend class Place;
		friend class Start;
	};
}                                                                                                                                        