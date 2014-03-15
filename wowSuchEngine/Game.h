#ifndef JOSHOENGINE_GAME_H_
#define JOSHOENGINE_GAME_H_

#include "JoshoEngine.h"
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include <fmod.hpp>

namespace JoshoEngine
{
	class JOSHO_API Game
	{
	public:
		// Singleton instance.
		static Game* instance();
		static Debug* debugInstance();
		static FMOD::System* fmodSystemInstance();

		// Current Window.
		Window* window;

		// Mouse position.
		Vector2 mouse;

		// Constructor
		Game();

		// Destructor.
		virtual ~Game();

		// Necessary Virtual Methods.

		/*!
		This method is called only once. At this point, the window has already
		been constructed, and it is safe to perform drawing. This is where
		content should be loaded and variables should be initialized if they
		weren't initialized by the constructor.
		@note This method must be implemented by a subclass.
		*/
		virtual void initialize() = 0;

		/*!
		This method is called once per frame during the game's run loop. All
		game logic such as movement and collision detection should go here.
		@note This method must be implemented by a subclass.
		@param deltaTime Elapsed time in seconds since update was called last.
		*/
		virtual void update(double deltaTime) = 0;

		/*!
		This method is called at least once per frame (it may also be called
		when the window needs to be redrawn for some reason). This is where
		all drawing should be done (including sprite animation).
		@note This method must be implemented by a subclass.
		@param deltaTime Elapsed time in seconds since draw was called last.
		*/
		virtual void draw(double deltaTime) = 0;

		// Base Public Methods.

		/*! Method to be called from `main` to run the game.
		@return Exit status code.
		*/
		int run();

		/*! Call this to terminate the game.
		@param status Exit status code.
		*/
		void terminate(int status);

		/*! Call this to switch to fullscreen-mode.
		@note registers callbacks automatically after switching.
		*/
		void toggleFullscreen();

		// Delegate Methods.

		/*! Called whenever the window is moved.
		@note This method is optional to implement.
		@param x The x coordinate the window was moved to.
		@param y The y coordinate the window was moved to.
		*/
		virtual void windowMoved(int x, int y) {};

		/*! Called whenever the window is resized.
		@note This method is optional to implement.
		@param width The window's new width.
		@param height The window's new height.
		*/
		virtual void windowResized(int width, int height) {};

		/*! Called when the window is closed. The game will automatically exit
		after this, so shutdown logic can go here before the destructor runs.
		@note This method is optional to implement.
		*/
		virtual void windowClosed() {};

		/*! Called when the window gains focus (it is clicked on and comes
		into the foreground) or loses focus (another window gains focus).
		@note This method is optional to implement.
		@param focused Whether the window gained or lost focus.
		*/
		virtual void windowFocused(bool focused) {};

		/*! Called when the window is minimized or unminimized.
		@note This method is optional to implement.
		@param minimized Whether the window was minimized or unminimized.
		*/
		virtual void windowMinimized(bool minimized) {};

		/*! Called when the window's framebuffer is resized.
		@note This method is optional to implement.
		@param width The framebuffer's new width.
		@param height The framebuffer's new height.
		*/
		virtual void framebufferResized(int width, int height) {};

		/*! Called when a mouse button is pressed down.
		@note This method is optional to implement.
		@param button The button that was pressed.
		@param mods Keyboard modifiers currently pressed.
		*/
		virtual void mouseDown(int button, int mods) {};

		/*! Called when a mouse button is released.
		@note This method is optional to implement.
		@param button The button that was released.
		@param mods Keyboard modifiers currently pressed.
		*/
		virtual void mouseUp(int button, int mods) {};

		/*! Called when the mouse cursor is moved when the window has focus.
		@note This method is optional to implement.
		@param pos New mouse position.
		*/
		virtual void mouseMoved(const Vector2& pos) {};

		/*! Called when the mouse moves across the window's border.
		@note This method is optional to implement.
		@param entered Whether the mouse entered or exited the window.
		*/
		virtual void mouseEntered(bool entered) {};

		/*! Called when the mouse or trackpad is scrolled.
		@note This method is optional to implement.
		@param offset Vector representing the magnitude and direction scrolled.
		*/
		virtual void scrolled(const Vector2& offset) {};

		/*! Called when a key is pressed (including special keys). The default
		action if not overridden is to terminate the game when ESC is pressed.
		@note This method is optional to implement.
		@param key The key that was pressed.
		@param scancode Hardware specific scancode (used to identify
		nonstandard keys for custom keymappings).
		@param mods Keyboard modifiers currently pressed.
		*/
		virtual void keyDown(int key, int scancode, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				this->terminate(0);
		};

		/*! Called when a key is released (including special keys).
		@note This method is optional to implement.
		@param key The key that was pressed.
		@param scancode Hardware specific scancode (used to identify
		nonstandard keys for custom keymappings).
		@param mods Keyboard modifiers currently pressed.
		*/
		virtual void keyUp(int key, int scancode, int mods) {};

		/*! Called when a key or special key repeats based on system settings.
		@note This method is optional to implement.
		@param key The key that was pressed.
		@param scancode Hardware specific scancode (used to identify
		nonstandard keys for custom keymappings).
		@param mods Keyboard modifiers currently pressed.
		*/
		virtual void keyRepeat(int key, int scancode, int mods) {};

		/*! Called when an ASCII key is pressed.
		@note This method is optional to implement.
		@param uc The ASCII character that would be typed if in a text field.
		*/
		virtual void charTyped(unsigned uc) {};

	protected:
		GLFWwindow* glWindow;

	private:
		Timer updateTimer;
		Timer drawTimer;

		static Game* game;
		static Debug* debug;
		static FMOD::System* fmod;

		int status;
		bool shutdown;

		void registerCallbacks();
		void initGL();
		void display();
		void mainLoop();

		// Friendly Callbacks.
		friend void _windowPositionCallback(GLFWwindow* w, int x, int y);
		friend void _windowSizeCallback(GLFWwindow* w, int width, int height);
		friend void _windowRefreshCallback(GLFWwindow* w);
	};
}

#endif
