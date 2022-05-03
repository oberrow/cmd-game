#if defined(_WIN64) && STATE && CMDGAME
#pragma once
#include "includes.hpp"
namespace game {
	class Movements {
	private:
		inline static int returnVal;
		inline static CONSOLE_SCREEN_BUFFER_INFO m_scr_buffer{};
	public:
		inline static COORD coordCpy = m_scr_buffer.dwCursorPosition;
		Movements(int key, CONSOLE_SCREEN_BUFFER_INFO buff)
		{
			m_scr_buffer = buff;
			switch (key)
			{
			case Keys::w:
			{
				//w key (lowercase)
				int currentCoordY = coordCpy.Y;
				coordCpy.Y--;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.Y == currentCoordY)
					coordCpy.Y--;
				break;
			}
			case Keys::W:
			{
				//W key (Uppercase)
				int currentCoordY = coordCpy.Y;
				coordCpy.Y--;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.Y == currentCoordY)
					coordCpy.Y--;
				break;
			}
			case Keys::s:
			{
				//s key (lowercase)
				int currentCoordY = coordCpy.Y;
				coordCpy.Y++;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.Y == currentCoordY)
					coordCpy.Y++;;
				break;
			}
			case Keys::S:
			{
				//S key (Uppercase)
				int currentCoordY = coordCpy.Y;
				coordCpy.Y++;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.Y == currentCoordY)
					coordCpy.Y++;
				break;
			}
			case Keys::a:
			{
				//a key (lowercase)
				int currentCoordX = coordCpy.X;
				coordCpy.X--;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.X == currentCoordX)
					coordCpy.X--;
				break;
			}
			case Keys::A:
			{
				//A key (Uppercase)
				int currentCoordX = coordCpy.X;
				coordCpy.X--;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.X == currentCoordX)
					coordCpy.X--;
				break;
			}
			case Keys::d:
			{
				//d key (lowercase)
				int currentCoordX = coordCpy.X;
				coordCpy.X++;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.X == currentCoordX)
					coordCpy.X++;
				break;
			}
			case Keys::D:
			{
				//D key (Uppercase)
				int currentCoordX = coordCpy.X;
				coordCpy.X++;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				if (coordCpy.X == currentCoordX)
					coordCpy.X++;
				break;
			}
			case Keys::space:
			{
				//Space key

				coordCpy.Y--;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				coordCpy.Y++;
				SetConsoleCursorPosition(OUT_HANDLE, coordCpy);
			}
			}
		}
	};
}
#endif