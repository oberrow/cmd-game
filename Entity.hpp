#pragma once
#include "includes.hpp"

namespace game {
	namespace entity {
		constexpr auto NULLENTITY = -999999;
		class Entity {
		private:
			COORD entityCoordinates;
			inline static unsigned int amountOfEntities;
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			bool killOnDestruction;
			int id = NULLENTITY;
		public:
			bool hasBeenKilled = false;
			Entity(int par_id, COORD whereToSummon, bool par_killOnDestruction = true)
				:killOnDestruction(par_killOnDestruction), id(par_id), entityCoordinates(whereToSummon)
			{
				if (id != NULLENTITY && amountOfEntities != 10) {
					amountOfEntities++;
					LPCWSTR ent = L"o\n|\n|";
					DWORD amount = 0;
					WriteConsoleOutputCharacter(handle, ent, 5, entityCoordinates, &amount);
				}
				else return;
			}

			bool kill()
			{
				if (id != NULLENTITY && amountOfEntities != 10) {
					amountOfEntities--;
					LPCWSTR killStr = L"\n\n\n";
					DWORD amountOfCharsWritten;
					WriteConsoleOutputCharacter(handle, killStr, 3, entityCoordinates, &amountOfCharsWritten);
					return true;
				}
				else return false;
			}
			~Entity()
			{
				if (killOnDestruction && id != NULLENTITY && amountOfEntities != 10 && !hasBeenKilled) {
					amountOfEntities--;
					LPCWSTR killStr = L"\n\n\n";
					DWORD amountOfCharsWritten;
					WriteConsoleOutputCharacter(handle, killStr, 3, entityCoordinates, &amountOfCharsWritten);
					hasBeenKilled = true;
				}
				else return;
			}
		};
	}
}