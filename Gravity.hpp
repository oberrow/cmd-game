#if defined(_WIN64) && STATE && CMDGAME
#pragma once
#include "log.hpp"
#include "includes.hpp"
#include "movements.hpp"

namespace game {
	class Gravity
	{
	private:
		Log l{ Log::levelInfoId };
		LPSTR isDown = (LPSTR)"\0";
		DWORD numberOfCharsRead = 0;
	public:
		Gravity(COORD pos, COORD maxSize)
		{
			ReadConsoleOutputCharacterA(
				GetStdHandle(STD_OUTPUT_HANDLE),
				isDown,
				1,
				COORD(pos.X, pos.Y++),
				&numberOfCharsRead
			);
			char down = isDown[0];
			for (auto i = 0; i < maxSize.X / 3; i++)
			{
				int toSub{};
				if (util::canBeDividedBy(i, 3))
				{
					toSub = 3 + i;
					if (down == ""[0] && numberOfCharsRead == 21)
					{
						pos.Y++;
						Movements::coordCpy = pos;
						SetConsoleCursorPosition(
							GetStdHandle(STD_OUTPUT_HANDLE),
							pos
						);
						break;
					}
				}
			}
		}
	};
}
#endif