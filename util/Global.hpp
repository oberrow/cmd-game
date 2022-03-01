#pragma once
#include "pch.h"

#define DLL _declspec(dllexport)

namespace util
{
	namespace Global
	{
		static HMODULE handle;
	}
}