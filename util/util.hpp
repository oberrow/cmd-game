#pragma once
#include "pch.h"
#include "Global.hpp"

namespace util
{
	typedef void(func_t)(void);
	// Only replaces 1 line!
	void DLL FindAndReplaceFile(const char* _fn, std::string toFind, std::string toReplace);
	/* Outputs a character at a specific coordinate with a color
	 Usage:
		LPCSTR text = "[] ";
		for (int i = 0; i < 3; i++)
		{
			util::OutputAtCoordA(GetOutputHandle(), 1, &text[i], COORD(i, []), BLUE);
		}
		With [] in COORD() is the Y coordinate
	*/
	void DLL OutputAtCoordA(HANDLE _handle, DWORD _length, LPCSTR _str, COORD _pos, WORD _attrib);
	/* Outputs a character at a specific coordinate with a color
	 Usage:
		LPCWSTR text = "[] ";
		for (int i = 0; i < 3; i++)
		{
			util::OutputAtCoordW(GetOutputHandle(), 1, &text[i], COORD(i, []), BLUE);
		}
		With [] in COORD() is the Y coordinate
	*/
	void DLL OutputAtCoordW(HANDLE _handle, DWORD _length, LPCWSTR _str, COORD _pos, WORD _attrib);
	// Only works with c-style arrays
	template<typename T>
	void DLL ForEach(T* in, size_t, func_t);
	// Only works with std::vector
	template<typename T>
	void DLL ForEach(std::vector<T>, func_t);
	// Checks if a number is even
	bool DLL isEven(int);
	struct DLL RunOnDestruction
	{
	private:
		void(*Run)();
	public:
		RunOnDestruction(void(Run)(void));
		~RunOnDestruction();

	};
	// Returns true if it found a number in the character return false otherwise
	bool DLL isdigit(char);
	template<typename T>
	// Only works with c style array's
	bool DLL in_array(T* _array, T _is, size_t size);
	// Only works with std::vector
	template<typename T>
	bool DLL in_vector(std::vector<T> _array, T _is);
	// Interupts the program so you can do something else
	void DLL Interrupt(void(Run)(void));
}