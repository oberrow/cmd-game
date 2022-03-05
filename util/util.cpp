#include "pch.h"
#include "util.hpp"

namespace util
{
	bool DLL isdigit(char _ch)
	{
		bool not_found = false;
		char num[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		for (int i = 0; i < 10; i++)
		{
			if (_ch == num[i])
			{
				return(true);
			}
			else
			{
				not_found = true;
			}
		}
		if (not_found)
		{
			return(false);
		}
	}
	template<typename T>
	void DLL ForEach(T* in, size_t size, func_t _Run)
	{
		for (int i = 0; i < size; i++)
		{
			_Run();
		}
	}
	template<typename T>
	void DLL ForEach(std::vector<T> in, func_t _Run)
	{
		for (int i = 0; i < in.size(); i++)
		{
			_Run();
		}
	}
	template<typename T>
	bool DLL in_array(T* _array, T _is, size_t size)
	{
		bool no = false;
		for (int i = 0; i < size; i++)
		{
			if (_array[i] == _is)
			{
				return true;
			}
			else {
				no = true;
			}
		}
		if (no == true)
		{
			return false;
		}
	}
	template<typename T>
	bool DLL in_vector(std::vector<T> _array, T _is)
	{
		bool no = false;
		for (int i = 0; i < _array.size(); i++)
		{
			if (_array[i] == _is)
			{
				return true;
			}
			else {
				no = true;
			}
		}
		if (no == true)
		{
			return false;
		}
	}
	// Interupts the program so you can do something else
	void DLL Interrupt(void(Run)(void))
	{
		Run();
	}
	RunOnDestruction::RunOnDestruction(void(Run)(void))
	{
		this->Run = Run;
	}
	RunOnDestruction::~RunOnDestruction()
	{
		Run();
	}
	void FindAndReplaceFile(const char* _fn, std::string toFind, std::string toReplace)
	{
		std::ifstream ifstr{ _fn };
		std::string file(std::istreambuf_iterator<char>{ ifstr }, {});
		size_t index = file.find(toFind);
		if (index == std::string::npos) {
			std::cerr << "Cannot find " << toFind << "!\n";
		}
		else
		{
			file.replace(index, toFind.size(), toReplace);
		}
		std::ofstream ofstr{ _fn };
		ofstr << file;
	}
	void DLL OutputAtCoordA(HANDLE _handle, DWORD _length, LPCSTR _str, COORD _pos, WORD _attrib)
	{
		DWORD _charWritten1;
		DWORD _charWritten2;
		WriteConsoleOutputCharacterA(_handle, _str, _length, _pos, &_charWritten1);
		WriteConsoleOutputAttribute(_handle, &_attrib, _length, _pos, &_charWritten2);
	}
	void DLL OutputAtCoordW(HANDLE _handle, DWORD _length, LPCWSTR _str, COORD _pos, WORD _attrib)
	{
		DWORD _charWritten1;
		DWORD _charWritten2;
		WriteConsoleOutputCharacterW(_handle, _str, _length, _pos, &_charWritten1);
		WriteConsoleOutputAttribute(_handle, &_attrib, _length, _pos, &_charWritten2);
	}
	bool DLL isEven(int _Num)
	{
		if (_Num % 2 == 0)
			return true;
		else
			return false;
	}
}
