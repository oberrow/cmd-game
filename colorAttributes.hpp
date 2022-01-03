#pragma once
#include "includes.h"

namespace game {
	struct colorAttributes {
		colorAttributes(WORD attrib) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attrib);
		}
		~colorAttributes() {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}
	};
}                                                                                                                                        
