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
		bool isNumber(std::string& line)
		{
			return (std::atoi(line.c_str()));
		}
		inline static int line = 0;
		inline static std::string filename = "";
	public:
		Config(Store& s, std::string fn) {
			Log l{ Log::levelErrorId };
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
				std::string values;
				if (line == 0)
				{
					in_fs.ignore(1000, '\n');
				}
				else {
					for (int i = 1; i < line; i++)
						in_fs.ignore(1000, '\n');
				}
				std::getline(in_fs, values);
				line++;

				in_fs.close();
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

				if (!isNumber(pre_Values) && pre_Values == " true")
					s.boolean_Out = true;
				else if (!isNumber(pre_Values) && pre_Values == " false")
					s.boolean_Out = false;
				else if (!isNumber(pre_Values))
					s.str_Out = pre_Values;
				else if (isNumber(pre_Values))
					s.int_Out = std::atoi(pre_Values.c_str());
				else
					l.levelWarn("Config file parser warning! Could not find any strings booleans or numbers after the \"=\" sign");
				/*std::stringstream ss;
				ss << pre_Values;
				int value_int{};
				std::string value_String{};
				bool value_Bool{};
				ss >> value_int >> value_Bool >> value_String;
				s.boolean_Out = value_Bool;
				s.int_Out = value_int;
				s.str_Out = value_String;
				int val = 0;
				for (int i = 0; i < 53; i++)
				{
					if (pre_Values != alphabet[i]) {
						val = std::stoi(pre_Values);
						s.int_Out = val;
					}
				}
				if (pre_Values == "true" || pre_Values == "false")
					s.boolean_Out = (bool)val;
				else
					s.str_Out = pre_Values;*/
		}
	};
}
