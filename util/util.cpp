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
}
