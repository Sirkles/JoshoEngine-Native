#ifndef JOSHOENGINE_INI_FILE_H_
#define JOSHOENGINE_INI_FILE_H_

#include "JoshoEngine.h"
#include <map>

namespace JoshoEngine
{
	class JOSHO_API IniFile
	{
	public:
		IniFile(std::string file);

		int parseError();

		std::string getString(std::string section, std::string name, std::string defaulValue);
		long getInteger(std::string section, std::string name, long defaultValue);
		double getReal(std::string section, std::string name, double defaultValue);
		bool getBoolean(std::string section, std::string name, bool defaultValue);
	private:
		std::string fileName;
		int error;

		std::map<std::string, std::string> values;

		static std::string makeKey(std::string section, std::string name);
		static int valueHandler(void* user, const char* section, const char* name, const char* value);
	};
}

#endif
