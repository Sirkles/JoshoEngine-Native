#ifndef JOSHOENGINE_WINDOW_H_
#define JOSHOENGINE_WINDOW_H_

#include "JoshoEngine.h"
#include "Color.h"
#include "Rectangle.h"

#include <GLFW/glfw3.h>

namespace JoshoEngine
{
	class JOSHO_API Window
	{
	public:
		Window(const char* title = "wow such title very creative wow", int x = 50, int y = 50, unsigned int width = 640, unsigned int height = 480, bool resizeable = false);

		~Window();

		void centerWindow();

		void setBackgroundColor(const Color& background);

		void clear();

		void render();

		const char* getTitle();

		void setTitle(const char* title);

		void setPreservesAspectRatio(bool preserve);

		bool preservesAspectRatio();

		Rectangle getBounds() const;

		unsigned int getWidth();

		unsigned int getHeight();

		void setSize(unsigned int width, unsigned int height);

		int getX();

		int getY();

		void setPosition(int x, int y);

		void hideCursor(bool hide);

		bool isFullscreen();

		void toggleFullscreen();

		void enableFullscreen();

		void disableFullscreen();

		GLFWwindow* currentWindowContext();

	private:
		const char* title;
		GLFWwindow* glWindow;
		GLFWwindow* fullscreenWindow;
		Color color;

		bool initialized;
		int x, y;
		unsigned int width, height;
		float planeWidth, planeHeight;
		float aspectRatio;
		bool resizeable, keepRatio;
		bool cursorHidden;

		void construct();
		void updateSize(unsigned int, unsigned int);
		void updateGL();
		void didMove(int, int);
		void didResize(int, int);

		friend class Game;
		friend void _windowPositionCallback(GLFWwindow* w, int x, int y);
		friend void _windowSizeCallback(GLFWwindow* w, int width, int height);
	};
}

#endif
