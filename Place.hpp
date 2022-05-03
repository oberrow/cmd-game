#if defined(_WIN64) && STATE && CMDGAME
#pragma once
#include "includes.hpp"
#include "colorAttributes.hpp"
#include "movements.hpp"
#include "log.hpp"

namespace game {
	class Place {
	private:
		Log l = Log::levelInfoId;
	public:
		Place(int blockId, CONSOLE_SCREEN_BUFFER_INFO buff) {
			unsigned char space = 32;
			std::cout << space;
			buff.dwCursorPosition.X += 3;
			switch (blockId) {
			case Keys::G:
			{
				{
					colorAttributes color = LIGHTGREEN;
					std::cout << "[]";
				}
				//const char* savegame, int blockId, COORD currentCoord


				break;
			}
			case Keys::g:
			{
				{
					colorAttributes color = LIGHTGREEN;
					std::cout << "[]";
				}

				break;
			}
			case Keys::r:
			{
				{
					colorAttributes color = colors::darkgray;
					std::cout << "[]";
				}


				break;
			}
			case Keys::R:
			{
				{
					colorAttributes color = colors::darkgray;
					std::cout << "[]";
				}


				break;
			}
			case Keys::B:
			{
				{
					colorAttributes color = LIGHTBLUE;
					std::cout << "[]";
				} 


				break;
			}
			case Keys::b:
			{
				{
					colorAttributes color = LIGHTBLUE;
					std::cout << "[]";
				}


				break;
			}
			case Keys::L:
			{
				{
					colorAttributes color = BROWN;
					std::cout << "[]";
				}


				break;
			}
			case Keys::l:
			{
				{
					colorAttributes color = BROWN;
					std::cout << "[]";
				}


				break;
			}
			case Keys::p:
			{
				{
					colorAttributes color = BLUE;
					std::cout << "[]";
				}


				break;
			}
			case Keys::P:
			{
				{
					colorAttributes color = BLUE;
					std::cout << "[]";
				}


				break;
			}
			case Keys::backspace:
			{
				colorAttributes color = LIGHTGRAY;
				printf_s("  ");
				Movements::coordCpy.X++;
				break;
			}
			default:
				break;
		}
		}
	};
} 
#endif