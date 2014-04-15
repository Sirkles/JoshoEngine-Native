#include "stdafx.h"
#include "IniFile.h"

#include "inih/ini.h"

using namespace JoshoEngine;

IniFile::IniFile(std::string file)
{
	this->fileName = file;

	this->error = ini_parse(file.c_str(), IniFile::valueHandler, this);
}

int IniFile::parseError()
{
	return this->error;
}

std::string IniFile::makeKey(std::string section, std::string name)
{
	std::string key = section + "." + name;

	// Convert to lower case to make section/name lookups case-insensitive.
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);

	return key;
}

std::string IniFile::getString(std::string section, std::string name, std::string defaultValue)
{
	std::string key = IniFile::makeKey(section, name);

	return (this->values.count(key) ? this->values[key] : defaultValue);
}

long IniFile::getInteger(std::string section, std::string name, long defaultValue)
{
	std::string valueString = this->getString(section, name, "");

	const char* value = valueString.c_str();
	char* end;

	long n = strtol(value, &end, 0);
	
	return (end > value ? n : defaultValue);
}

double IniFile::getReal(std::string section, std::string name, double defaultValue)
{
	std::string valueString = this->getString(section, name, "");

	const char* value = valueString.c_str();
	char* end;

	double n = strtod(value, &end);

	return (end > value ? n : defaultValue);
}

bool IniFile::getBoolean(std::string section, std::string name, bool defaultValue)
{
	std::string valueString = this->getString(section, name, "");

	// Convert to lower case to make string comparisons case-insensitive
	std::transform(valueString.begin(), valueString.end(), valueString.begin(), ::tolower);

	if (valueString == "true" || valueString == "yes" || valueString == "on" || valueString == "1")
		return true;
	else if (valueString == "false" || valueString == "no" || valueString == "off" || valueString == "0")
		return false;
	else
		return defaultValue;
}

int IniFile::valueHandler(void* user, const char* section, const char* name, const char* value)
{
	IniFile* iniReader = (IniFile*)user;
	std::string key = IniFile::makeKey(section, name);

	if (iniReader->values[key].size() > 0)
		iniReader->values[key] += "\n";

	iniReader->values[key] += value;

	return 1;
}
