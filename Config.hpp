#pragma once
#include "includes.hpp"
#include "log.hpp"
namespace game {
	struct Store {
		std::string str_Out{};
		int int_Out{};
		bool boolean_Out{};
		friend std::ostream& operator<<(std::ostream& os, const Store& s) {
			std::string boolVal;
			if (s.boolean_Out == true)
				boolVal = "true";
			else
				boolVal = "false";
			os << s.str_Out << ' ' << s.int_Out << ' ' << boolVal;
			return os;
		}
	};
	class Config
	{
	private:
		size_t element = 0;
		bool isNumber(std::string& line)
		{
			return (std::atoi(line.c_str()));
		}
		inline static int line = 0;
		inline static std::string filename = "";
	public:
		std::vector<game::Store> Data;
		Config(std::string fn) {
			Log l{ Log::levelInfoId };
			filename = fn;
			if (!std::filesystem::exists(fn))
			{
				l.levelError("File \"" + fn + "\" doesn't exist");
				throw("File \"" + fn + "\" doesn't exist");
			}
			std::ifstream in_fs;
			in_fs.open(filename);
			in_fs.clear();
			in_fs.seekg(0, std::ios::beg);
			if (filename != fn)
				line = 0;
			std::string values;
			while (std::getline(in_fs, values))
			{	
				std::string pre_Values{};
			/*std::string alphabet[53] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
	"w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };*/
				size_t nval = values.find("=");
				if (nval != std::string::npos)
					pre_Values = values.substr(nval + 1);

				if (!pre_Values.empty())
					;
				else
					l.levelError("\nAn error has occured in the config file parser! Missing an \"=\" sign. Filename is " + fn);
				game::Store toVec = { };
				Data.push_back(toVec);
				element++;
				if (Data.size() == 1)
				{
					element--;
				}
				if (element >= Data.size())
					GameInterrupt("Current Element of vector \"Data\" is greater then the size!");
				if (!isNumber(pre_Values) && pre_Values == " true")
				{
					if (Data.size() == 1)
						Data[element].boolean_Out = true;
					else
						Data[element - 1].boolean_Out = true;
				}
				else if (!isNumber(pre_Values) && pre_Values == " false")
				{
					if (Data.size() == 1)
						Data[element].boolean_Out = false;
					else
						Data[element - 1].boolean_Out = false;
				}
				else if (!isNumber(pre_Values))
				{
					if (Data.size() == 1)
						Data[element].str_Out = pre_Values;
					else
						Data[element - 1].str_Out = pre_Values;
				}
				else if (isNumber(pre_Values))
				{
					if (Data.size() == 1)
						Data[element].int_Out = std::atoi(pre_Values.c_str());
					else
						Data[element - 1].int_Out = std::atoi(pre_Values.c_str());
				}
				else
					l.levelWarn("Config file parser warning! Could not find any strings booleans or numbers after the \"=\" sign");

		}
		in_fs.close();
		}
	};
}
