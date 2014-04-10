#include "stdafx.h"
#include "IniFile.h"

using namespace JoshoEngine;

IniFile::IniFile(const char* file)
{
	this->fileName = file;

	this->iniFile.open(this->fileName);

	if (this->iniFile.fail())
	{
		std::string errorMessage = "Unable to open the configuration file: " + std::string(this->fileName) + "\nEnsure the file exists and has read permissions.";

		throw new std::runtime_error(errorMessage);
	}

	this->valueDictionary = std::unordered_map<const char*, const char*>();
}

IniFile::~IniFile()
{
	this->iniFile.close();
}

bool IniFile::getValue(const char* key, const char* value) const
{
	try
	{
		value = this->valueDictionary.at(key);
		return true;
	}
	catch (std::out_of_range ex)
	{
		value = NULL;
		return false;
	}
}

bool IniFile::isComment(const char* line)
{
	char firstChar = *line;
	char secondChar = *(line++);

	if (firstChar == ';' || firstChar == '#' || (firstChar == '/' && secondChar == '/'))
		return true;
	else
		return false;
}

bool IniFile::isSection(const char* line, const char* sectionName)
{
	char firstChar = *line;

	std::string sectionContainer; // Easier to append. :P

	if (firstChar == '[')
	{
		for (char* i = (char*)(line + 1); *i; i++)
		{
			if (*i == ']')
			{
				sectionName = sectionContainer.c_str();
				return true;
			}

			sectionContainer += *i;
		}

		// If we didn't run into the ending bracket ']'
		throw new std::runtime_error("Missing ending bracket for section declaration.");
	}
	else
	{
		sectionName = NULL;
		return false;
	}
}
