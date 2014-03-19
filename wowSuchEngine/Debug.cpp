#include "stdafx.h"
#include "JoshoEngine.h"
#include "Debug.h"
#include "Game.h"

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

double Debug::calculateFPS(std::string windowTitle, double timeInterval)
{
	// Static values which only get initialised the first time the function runs
	static double startTime = glfwGetTime(); // Set the initial time to now
	static double fps = 0.0;           // Set the initial FPS value to 0.0

	// Set the initial frame count to -1.0 (it gets set to 0.0 on the next line). Because
	// we don't have a start time we simply cannot get an accurate FPS value on our very
	// first read if the time interval is zero, so we'll settle for an FPS value of zero instead.
	static double frameCount = -1.0;

	// Here again? Increment the frame count
	frameCount++;

	// Ensure the time interval between FPS checks is sane (low cap = 0.0 i.e. every frame, high cap = 10.0s)
	if (timeInterval < 0.0)
	{
		timeInterval = 0.0;
	}
	else if (timeInterval > 10.0)
	{
		timeInterval = 10.0;
	}

	// Get the duration in seconds since the last FPS reporting interval elapsed
	// as the current time minus the interval start time
	double duration = glfwGetTime() - startTime;

	// If the time interval has elapsed...
	if (duration > timeInterval)
	{
		// Calculate the FPS as the number of frames divided by the duration in seconds
		fps = frameCount / duration;

		// If the user specified a window title to append the FPS value to...
		if (windowTitle != "NONE")
		{
			// Convert the fps value into a string using an output stringstream
			std::ostringstream stream;
			stream << fps;
			std::string fpsString = stream.str();

			// Append the FPS value to the window title details
			windowTitle += " | FPS: " + fpsString;

			// Convert the new window title to a c_str and set it
			const char* pszConstString = windowTitle.c_str();
			glfwSetWindowTitle(Game::instance()->window->currentWindowContext(), pszConstString);
		}
		else // If the user didn't specify a window to append the FPS to then output the FPS to the console
		{
			std::cout << "FPS: " << fps << std::endl;
		}

		// Reset the frame count to zero and set the initial time to be now
		frameCount = 0.0;
		startTime = glfwGetTime();
	}

	// Return the current FPS - doesn't have to be used if you don't want it!
	return fps;
}

double Debug::calculateFPS(double timeInterval)
{
	return this->calculateFPS(Game::instance()->window->getTitle(), timeInterval);
}
