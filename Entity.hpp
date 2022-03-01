#pragma once
#include "includes.hpp"

namespace game {
	namespace entity {
		constexpr auto NULLENTITY = -1000;
		constexpr auto NULLTYPE = -100;
		constexpr auto PlayerType = 0;
		constexpr auto NPCBaseType = 1;
		// Base type for ALL entities whether it be players, npc's
		class Entity {
		protected:
			Log l = Log::levelInfoId;
			COORD entityCoordinates;
			inline static unsigned int amountOfEntities;
			HANDLE handle = nullptr;
			bool killOnDestruction;
			static inline std::vector<int> id;
			size_t element{};
			LPCWSTR ent = L"";
			int type = NULLTYPE;
			void ChangeType(int type) { this->type = type; }
		public:
			bool hasBeenKilled = false;
			Entity(int par_id, COORD whereToSummon, bool par_killOnDestruction = true)
				:killOnDestruction(par_killOnDestruction), entityCoordinates(whereToSummon)
			{
				handle = GetOutputHandle();
				id.push_back(par_id);
				for (auto i : id)
					element++;
			}
			virtual void summon()
			{
				/*DWORD amount = 0;
				if (id[element] != NULLENTITY && amountOfEntities != 10) {
					amountOfEntities++;
				}
				else return;
				WriteConsoleOutputCharacter(handle, ent, 5, entityCoordinates, &amount);*/
				if(type == NULLTYPE)
					l.levelWarn("You are using an entity that has no type!");
			}
			virtual bool kill()
			{
				if (id[element - 1] != NULLENTITY && amountOfEntities != 10) {
					if (type == NULLTYPE)
						l.levelWarn("You are using an entity that has no type!");
					return true;
				}
				else return false;
			}
			virtual ~Entity()
			{
				if (killOnDestruction && id[element - 1] != NULLENTITY && amountOfEntities != 10 && !hasBeenKilled) 
				{
					kill();
					hasBeenKilled = true;
				}
				else return;
			}
		};
		// This type will be able to add multiplayer to this game
		// Type for Players
		class Player : public Entity 
		{
		private:
			//size_t currentElement = element - 1;
			std::string playername = "Test Player";
		public:
			Player(int id, COORD whereToSummon, bool killOnDestruction, std::string playername):Entity(id, whereToSummon, killOnDestruction)
			{
				this->playername = playername;
				ChangeType(PlayerType);
				summon();
			}
			COORD getCoordinates() { return entityCoordinates; }
			void summon()
			{
				DWORD amount = 0;
				if (id[element - 1] != NULLENTITY && amountOfEntities != 10) {
					amountOfEntities++;
				}
				else return;
				ent = L"o";
				COORD copyOfEntityCoords = entityCoordinates;
				WriteConsoleOutputCharacter(handle, ent, 1, copyOfEntityCoords, &amount);
				ent = L"|";
				copyOfEntityCoords.Y++;
				WriteConsoleOutputCharacter(handle, ent, 1, copyOfEntityCoords, &amount);
				ent = L"^";
				copyOfEntityCoords.Y++;
				WriteConsoleOutputCharacter(handle, ent, 1, copyOfEntityCoords, &amount);
			}
			bool kill()
			{
				DWORD amount = 0;
				if (id[element - 1] != NULLENTITY && !hasBeenKilled) {
					amountOfEntities--;

				ent = L" ";
				COORD copyOfEntityCoords = entityCoordinates;
				WriteConsoleOutputCharacter(handle, ent, 2, copyOfEntityCoords, &amount);
				copyOfEntityCoords.Y++;
				WriteConsoleOutputCharacter(handle, ent, 2, copyOfEntityCoords, &amount);
				copyOfEntityCoords.Y++;
				WriteConsoleOutputCharacter(handle, ent, 2, copyOfEntityCoords, &amount);
				l.levelInfo(playername + " has left the game!");
				return true;
				}
				else return false;
			}
			~Player()
			{
				if (killOnDestruction && id[element - 1] != NULLENTITY && amountOfEntities != 10 && !hasBeenKilled) {
					kill();
					hasBeenKilled = true;
				}
				else return;
			}
			friend class Movements;
		};
	}
}