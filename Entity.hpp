#include "GlobalVars.hpp"
#if ENTITY_TESTING
#undef CMDGAME
#undef STATE
#define STATE 0x01
#define CMDGAME 0x01
#endif
#if defined(_WIN64) && ENTITY_TESTING && STATE && CMDGAME
#pragma once
#include <array>
#include <random>
#include "includes.hpp"
#include "log.hpp"

namespace game {
	namespace entity {
		constexpr auto NULLENTITY = -1000;
		constexpr auto NULLTYPE = -100;
		enum class types
		{
			player,
			npc
		};
		enum class npc_types
		{
			basic
		};
		std::array<int, 2> types_array = { 0, 1 };
		// Base type for ALL entities whether it be players, npc's
		class Entity {
		protected:
			inline static Log l = Log::levelInfoId;
			COORD entityCoordinates;
			inline static unsigned int amountOfEntities;
			HANDLE handle = nullptr;
			bool killOnDestruction;
			static inline std::vector<types> id;
			size_t element{};
			LPCWSTR ent = L"";
			int type = NULLTYPE;
			void ChangeType(int type) { if(is_type_valid(type)) this->type = type; }
		public:
			bool hasBeenKilled = false;
			Entity(types par_id, COORD whereToSummon, bool par_killOnDestruction = true)
				:killOnDestruction(par_killOnDestruction), entityCoordinates(whereToSummon)
			{
				handle = GetStdHandle(((DWORD)-11));
				id.push_back(par_id);
				for (auto i : id)
					element++;
			}
			bool is_type_valid() 
			{ 
				bool valid = false;
				for (auto i : types_array)
				{
					if (type == types_array[i])
					{
						valid = true;
					}
				}
				return valid;
			}
			bool is_type_valid(int ntype)
			{
				bool valid = false;
				for (auto i : types_array)
				{
					if (ntype == types_array[i])
					{
						valid = true;
					}
				}
				return valid;
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
				if ((int)id[element - 1] != NULLENTITY && amountOfEntities != 10 && !hasBeenKilled) {
					if (type == NULLTYPE)
						l.levelWarn("You are using an entity that has no type!");
					return true;
				}
				else return false;
			}
			virtual ~Entity()
			{
				if (killOnDestruction && (int)id[element - 1] != NULLENTITY && amountOfEntities != 10 && !hasBeenKilled) 
				{
					if(kill())
					hasBeenKilled = true;
				}
				else return;
			}
		};
		/* 
		This type will be able to add multiplayer to this game * This isn't finished do not use *
		Type for Players
		*/
		class Player : public Entity 
		{
		private:
			// The name of the player
			std::string m_PlayerName = "Test Player";
			std::string m_Savegame;
			Chat m_Chat = m_Savegame;
		public:
			std::string GetPlayerName()
			{
				return m_PlayerName;
			}
			// int key can be any value in enumuration "game::Keys"
			void MovePlayer(int key)
			{
				switch (key)
				{
				case Keys::W:
				{
					kill(false);
					entityCoordinates.Y--;
					summon();
					break;
				}
				case Keys::w:
				{
					kill(false);
					entityCoordinates.Y--;
					summon();
					break;
				}
				case Keys::S:
				{
					kill(false);
					entityCoordinates.Y++;
					summon();
					break;
				}
				case Keys::s:
				{
					kill(false);
					entityCoordinates.Y++;
					summon();
					break;
				}
				case Keys::A:
				{
					kill(false);
					entityCoordinates.X--;
					summon();
					break;
				}
				case Keys::a:
				{
					kill(false);
					entityCoordinates.X--;
					summon();
					break;
				}
				case Keys::D:
				{
					kill(false);
					entityCoordinates.X++;
					summon();
					break;
				}
				case Keys::d:
				{
					kill(false);
					entityCoordinates.X++;
					summon();
					break;
				}
				}
			}
			// int key can be any value in enumuration "game::Keys"
			void PlaceBlock(int key)
			{
				LPCSTR str = "[] ";
				switch (key)
				{
				case Keys::G:
				{

					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 3; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str[i],
							pos,
							LIGHTGREEN
						);
					}
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				case Keys::g:
				{
					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 3; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str[i],
							pos,
							LIGHTGREEN
						);
						MovePlayer(Keys::D);
					}
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				case Keys::B:
				{

					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 3; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str[i],
							pos,
							LIGHTBLUE
						);

						MovePlayer(Keys::D);
					}
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				case Keys::b:
				{

					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 3; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str[i],
							pos,
							LIGHTBLUE
						);
					}
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				case Keys::L:
				{

					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 3; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str[i],
							pos,
							BROWN
						);

						MovePlayer(Keys::D);
					}
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				case Keys::l:
				{
					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 3; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str[i],
							pos,
							BROWN
						);

						MovePlayer(Keys::D);
					}
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				case Keys::P:
				{
					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 3; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str[i],
							pos,
							BLUE
						);

						MovePlayer(Keys::D);
					}
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				case Keys::p:
				{
					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 3; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str[i],
							pos,
							BLUE
						);

						MovePlayer(Keys::D);
					}
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				case Keys::R:
				{
					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 3; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str[i],
							pos,
							LIGHTGRAY
						);

						MovePlayer(Keys::D);
					}
					MovePlayer(Keys::D);
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				case Keys::r:
				{
					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 3; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str[i],
							pos,
							LIGHTGRAY
						);

						MovePlayer(Keys::D);
					}
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				case Keys::backspace:
				{
					LPCSTR str2 = "  ";
					COORD pos = { entityCoordinates.X, entityCoordinates.Y };
					pos.X++;
					pos.Y++;
					for (int i = 0; i < 2; i++)
					{
						pos.X = pos.X + i;
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&str2[i],
							pos,
							LIGHTGRAY
						);

						MovePlayer(Keys::D);
					}
					kill(false);
					entityCoordinates.X = entityCoordinates.X + 3;
					summon();
					break;
				}
				}
			}
			Player(const Player&) = delete;
			Player(COORD whereToSummon, bool killOnDestruction, std::string playername, std::string savegame):Entity(types::player, whereToSummon, killOnDestruction)
			{
				m_Chat.chat(playername + " has joined the game!");
				ChangeType(types_array[(int)types::player]);
				this->m_Savegame = savegame;
				this->m_PlayerName = playername;
				summon();
			}
			COORD getCoordinates() { return entityCoordinates; }
			void summon() override
			{
				DWORD amount = 0;
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
			bool kill(bool displayMessage = true)
			{
				DWORD amount = 0;
				ent = L" ";
				COORD copyOfEntityCoords = entityCoordinates;
				WriteConsoleOutputCharacter(handle, ent, 1, copyOfEntityCoords, &amount);
				copyOfEntityCoords.Y++;
				WriteConsoleOutputCharacter(handle, ent, 1, copyOfEntityCoords, &amount);
				copyOfEntityCoords.Y++;
				WriteConsoleOutputCharacter(handle, ent, 1, copyOfEntityCoords, &amount);
				if(displayMessage)
					m_Chat.chat(m_PlayerName + " has left the game!");
				return true;
			}
			~Player()
			{
				if (killOnDestruction && (int)id[element - 1] != NULLENTITY && amountOfEntities != 10 && !hasBeenKilled) {
					kill();
					hasBeenKilled = true;
				}
				else return;
			}
			friend class Movements;
		};
		/*
			Type for all npc's
		*/
		class Npc : public Entity
		{
		private:
			using uchar1_t = unsigned char;
			bool flag_log_summon_message = true;
			COORD GetRandomCoordinates()
			{
				std::random_device rseed;
				std::mt19937 rng(rseed());
				std::uniform_int_distribution<short> dist(-1, 1);
				short x{ dist(rng) + entityCoordinates.X };
				short y{ dist(rng) + entityCoordinates.Y };
				return COORD{ x, y };
			}
			LPCSTR m_EntityTexture = LPSTR("unavalible");
			size_t m_EntityTextureLength = 11;
			npc_types m_NPCTypes;
		public:
			COORD RandomMoveNPC()
			{
				flag_log_summon_message = false;
				util::RunOnDestruction rod([&]()
					{
						flag_log_summon_message = true;
					}
				);
				entityCoordinates = GetRandomCoordinates();
				kill();
				summon();
				return entityCoordinates;
			}
			Npc() = delete;
			Npc(const Npc&) = delete;
			Npc(size_t textureSize, npc_types this_type, LPCSTR entStr, COORD whereToSummon, bool killOnDestruction = true)
				:Entity(types::npc, whereToSummon, killOnDestruction),
				m_EntityTexture(entStr), m_EntityTextureLength(textureSize)
			{
				ChangeType((int)types::npc);
				summon();
			}
			void summon() override
			{
				if (flag_log_summon_message)
				{
					std::stringstream ss;
					ss << "NPC Summoned at coordinates " << util::CoordToString(entityCoordinates) << "Entity Format " << m_EntityTexture;
					l.levelInfo(ss.str(), PRINT_ON_LOG_CONSOLE);
				}
				char c = '\0';
				for(int i = 0; i < m_EntityTextureLength; i++)
				{ 
					c = m_EntityTexture[i];
					if(c != '\n')
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&c,
							entityCoordinates,
							util::colors::lightgray
						);
					else if(c == '\n')
						util::OutputAtCoordA(
							GetStdHandle(STD_OUTPUT_HANDLE),
							1,
							&c,
							COORD(entityCoordinates.X, entityCoordinates.Y - 1),
							util::colors::lightgray
						);
				}
			}
			bool kill() override
			{
				DWORD amount = 0;
				if (!hasBeenKilled)
				{
					char c = '\0';
					char empty = 32;
					for (int i = 0; i < m_EntityTextureLength; i++)
					{
						c = m_EntityTexture[i];
						if(c != '\n')
							util::OutputAtCoordA(
								GetStdHandle(STD_OUTPUT_HANDLE),
								1,
								&empty,
								entityCoordinates,
								colors::lightgray
							);
						else if (c == '\n')
						{
							util::OutputAtCoordA(
								GetStdHandle(STD_OUTPUT_HANDLE),
								1,
								&empty,
								COORD(entityCoordinates.X, entityCoordinates.Y - 1),
								colors::lightgray
							);
						}
					}
					return true;
				}
				return false;
			}
			~Npc()
			{
				kill();
			}
		};
	}
}
#endif