#ifndef JOSHOENGINE_INI_FILE_H_
#define JOSHOENGINE_INI_FILE_H_

#include "JoshoEngine.h"
#include <unordered_map>
#include <fstream>

namespace JoshoEngine
{
	class JOSHO_API IniFile
	{
	public:
		IniFile(const char* file);
		~IniFile();

		// value should be NULL.
		bool getValue(const char* key, const char* value) const;
	private:
		const char* fileName;
		std::ifstream iniFile;
		std::unordered_map<const char*, const char*> valueDictionary;

		bool isComment(const char* line);
		
		// sectionName will be assigned at function runtime.
		bool isSection(const char* line, const char* sectionName);
	};
}

#endif
