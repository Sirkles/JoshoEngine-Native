#include "stdafx.h"
#include "JoshoEngine.h"
#include "Debug.h"

using namespace JoshoEngine;

Debug::Debug()
{
	// Get console information.
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int a = csbi.wAttributes;

	// Get the current foreground color.
	this->foreground = a % 16;

	// Get the current background color.
	this->background = (a / 16) % 16;
}

void Debug::debugf(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int nBuf;
	char szBuffer[1024];
	nBuf = vsprintf_s(szBuffer, fmt, args);
	OutputDebugStringA(szBuffer);
	va_end(args);
}

void Debug::setConsoleColor(int fg, int bg)
{
	// We don't want the foreground and background to be the same.
	//if ((fg % 16) == (bg % 16)) fg++;

	fg %= 16;
	bg %= 16;

	unsigned short wAttributes = ((unsigned int)bg << 4) | (unsigned int)fg;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wAttributes);
}

void Debug::resetConsoleColor()
{
	this->setConsoleColor(this->foreground, this->background);
}

int Debug::getConsoleForegroundColor()
{
	// Get console information.
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int a = csbi.wAttributes;

	// Get the current foreground color.
	return a % 16;
}

int Debug::getConsoleBackgroundColor()
{
	// Get console information.
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int a = csbi.wAttributes;

	// Get the current background color.
	return (a / 16) % 16;
}

void Debug::setConsoleCursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	consoleCursorInfo.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(GENERIC_ALL), &consoleCursorInfo);
}

void Debug::setConsoleCursorPoint(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD placeCursorHere;
	placeCursorHere.X = x;
	placeCursorHere.Y = y;

	SetConsoleCursorPosition(hConsole, placeCursorHere);
}

void Debug::clearConsole()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 }; // here's where we'll home the cursor
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer info
	DWORD dwConSize; // number of character cells in the current buffer

	// get the number of character cells in the current buffer
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill the entire screen with blanks
	FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);

	// get the current text attribute
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	// now set the buffer's attributes accordingly
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

	// put the cursor at (0, 0)
	SetConsoleCursorPosition(hConsole, coordScreen);
}

bool Debug::isRemoteDebuggerPresent()
{
	BOOL remoteDebugger;
	CheckRemoteDebuggerPresent(GetCurrentProcess(), &remoteDebugger);
	return remoteDebugger;
}

bool Debug::isLocalDebuggerPresent()
{
	return IsDebuggerPresent();
}

bool Debug::isDebuggerAttached()
{
	BOOL remoteDebugger;
	CheckRemoteDebuggerPresent(GetCurrentProcess(), &remoteDebugger);
	return IsDebuggerPresent() || remoteDebugger;
}

void Debug::sleepCurrentThread(unsigned int milliseconds)
{
#ifdef WIN32
	Sleep(milliseconds);
#endif
}

const char* Debug::getGLVersion()
{
	return (const char*)glGetString(GL_VERSION);
}
