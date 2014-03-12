#ifndef JOSHOENGINE_DEBUG_H_
#define JOSHOENGINE_DEBUG_H_

#if !(defined WIN32 || defined WIN64)
#error "This class most likely won't compile unless you are running Windows. Sorry about that."
#endif

#include "JoshoEngine.h"

namespace JoshoEngine
{
	class JOSHO_API Debug
	{
	public:
		enum Colors : unsigned int
		{
			Black = 0,
			DarkBlue = 1,
			DarkGreen = 2,
			DarkAqua, DarkCyan = 3,
			DarkRed = 4,
			DarkPurple = 5, DarkPink = 5, DarkMagenta = 5,
			DarkYellow = 6,
			DarkWhite = 7,
			Gray = 8,
			Blue = 9,
			Green = 10,
			Aqua = 11, Cyan = 11,
			Red = 12,
			Purple = 13, Pink = 13, Magenta = 13,
			Yellow = 14,
			White = 15
		};

		Debug();

		void debugf(const char* fmt, ...);
		void setConsoleColor(int fg, int bg);
		int getConsoleBackgroundColor();
		int getConsoleForegroundColor();
		void setConsoleCursorVisible(bool visible);
		void setConsoleCursorPoint(int x, int y);
		void clearConsole();
		void resetConsoleColor();
		bool isRemoteDebuggerPresent();
		bool isLocalDebuggerPresent();
		bool isDebuggerAttached();
		void sleepCurrentThread(unsigned int milliseconds);
		const char* getGLVersion();
	private:
		int foreground;
		int background;
	};
}

#endif
