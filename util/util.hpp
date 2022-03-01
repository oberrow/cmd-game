#pragma once
#include "pch.h"
#include "Global.hpp"

namespace util
{
	// Returns true if it found a number in the character return false otherwise
	bool DLL isdigit(char);
	template<typename T>
	// Only works with c style array's
	bool DLL in_array(T* _array, T _is, size_t size);
	template<typename T>
	// Only works with c style array's
	bool DLL in_array(T* _array, T _is, size_t size);
	// Interupts the program so you can do something else
	void DLL Interrupt(void(Run)(void));
}