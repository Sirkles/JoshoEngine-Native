#include "stdafx.h"

#if defined _WIN32 || defined _WIN64
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#endif

#include "JoshoEngine.h"
#include "Game.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

using namespace JoshoEngine;

namespace JoshoEngine
{
	// GLFW Callbacks
	void _errorCallback(int error, const char* description);
	void _windowPositionCallback(GLFWwindow* w, int x, int y);
	void _windowSizeCallback(GLFWwindow* w, int width, int height);
	void _windowCloseCallback(GLFWwindow* w);
	void _windowRefreshCallback(GLFWwindow* w);
	void _windowFocusCallback(GLFWwindow* w, int dir);
	void _windowIconifyCallback(GLFWwindow* w, int dir);
	void _framebufferSizeCallback(GLFWwindow* w, int width, int height);
	void _mouseButtonCallback(GLFWwindow* w, int button, int action, int mods);
	void _cursorPositionCallback(GLFWwindow* w, double x, double y);
	void _cursorEnterCallback(GLFWwindow* w, int dir);
	void _mouseScrollCallback(GLFWwindow* w, double x, double y);
	void _keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods);
	void _charCallback(GLFWwindow* w, unsigned c);

	// Singleton Instance of the Game and Debug assistants, and the FMOD System
	Game* Game::game;
	Debug* Game::debug;
	FMOD::System* Game::fmod;
}

Game::Game()
{
	glfwInit();

	window = new Window();

	Game::game = this;
	Game::debug = new Debug();

	this->initAudio();

	shutdown = false;

	// Initialize random number generator.
	srand(time(NULL));

	rand();
	rand();
	rand();
}

void Game::initAudio()
{
	// Init FMOD.
	FMOD_RESULT result = FMOD::System_Create(&Game::fmod);

	// Make sure it was created ok.
	if (result != FMOD_OK)
	{
		std::cerr << "Error: Couldn't start up FMOD!" << std::endl;
		exit(-1);
	}

	// Initialize FMOD with 512 channels of audio, and normally.
	result = Game::fmod->init(512, FMOD_INIT_NORMAL, NULL);

	if (result != FMOD_OK)
	{
		std::cerr << "Error: Couldn't initialize FMOD!" << std::endl;
		exit(-1);
	}

	// Check version, make sure DLL is what we compiled with.
	unsigned int fmodVersion;
	this->fmod->getVersion(&fmodVersion);

	if (fmodVersion < FMOD_VERSION)
	{
		std::cerr << "Error: Detected an old version of FMOD, please use the latest FMOD library!" << std::endl;
		exit(-2);
	}

	// Check if we have audio capabilities
	int numCards = 0;
	this->fmod->getNumDrivers(&numCards);

	if (numCards == 0)
	{
		std::cerr << "Error: Couldn't detect any audio devices. Disabling audio..." << std::endl;

		this->fmod->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
	}
}

Game::~Game()
{
	delete window;

	Game::fmod->release();

	delete Game::debug;

	glfwTerminate();

	terminate(0);
}

Game* Game::instance()
{
	return Game::game;
}

Debug* Game::debugInstance()
{
	return Game::debug;
}

FMOD::System* Game::fmodSystemInstance()
{
	return Game::fmod;
}

void Game::initGL()
{
	glDepthMask(false);
}

void Game::display()
{
	window->clear();

	draw(drawTimer.tick());

	window->render();
}

void Game::updateAudio()
{
	this->fmod->update();
}

void Game::mainLoop()
{
	while (!shutdown && !glfwWindowShouldClose(glWindow))
	{
		this->updateAudio();

		update(updateTimer.tick());
		display();

		glfwPollEvents();
	}
}

int Game::run()
{
	// Set our render window to the window's render window. (that makes sense)
	glWindow = this->window->currentWindowContext();

	// Register callbacks.
	this->registerCallbacks();

	// Init OpenGL
	this->initGL();

	// Call the user init method.
	this->initialize();

	// Reset the update and draw timers.
	this->updateTimer.reset();
	this->drawTimer.reset();

	// Call the main loop.
	this->mainLoop();

	// Free memory by suicide.
	delete this;

	// Return this to main.
	return status;
}

void Game::terminate(int exitStatus)
{
	shutdown = true;
	status = exitStatus;
}

void JoshoEngine::_errorCallback(int error, const char* description)
{
	std::cerr << "Error " << error << ": " << description << std::endl;
	exit(1);
}

void JoshoEngine::_windowPositionCallback(GLFWwindow* w, int x, int y)
{
	Game& g = *Game::instance();
	g.window->didMove(x, y);
	g.windowMoved(x, y);
}

void JoshoEngine::_windowSizeCallback(GLFWwindow* w, int width, int height)
{
	Game& g = *Game::instance();
	g.window->didResize(width, height);
	g.windowResized(width, height);
}

void JoshoEngine::_windowCloseCallback(GLFWwindow* w)
{
	Game::instance()->windowClosed();
}

void JoshoEngine::_windowRefreshCallback(GLFWwindow* w)
{
	Game::instance()->display();
}

void JoshoEngine::_windowFocusCallback(GLFWwindow* w, int dir)
{
	Game::instance()->windowFocused(dir);
}

void JoshoEngine::_windowIconifyCallback(GLFWwindow* w, int dir)
{
	Game::instance()->windowMinimized(dir);
}

void JoshoEngine::_framebufferSizeCallback(GLFWwindow* w, int width, int height)
{
	Game::instance()->framebufferResized(width, height);
}

void JoshoEngine::_mouseButtonCallback(GLFWwindow* w, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		Game::instance()->mouseDown(button, mods);
		break;

	case GLFW_RELEASE:
		Game::instance()->mouseUp(button, mods);
		break;

	default:
		break;
	}
}

void JoshoEngine::_cursorPositionCallback(GLFWwindow* w, double x, double y)
{
	Game& g = *Game::instance();
	g.mouse = { (float)x, (float)y };
	g.mouseMoved({ (float)x, (float)y });
}

void JoshoEngine::_cursorEnterCallback(GLFWwindow* w, int dir)
{
	Game::instance()->mouseEntered(dir);
}

void JoshoEngine::_mouseScrollCallback(GLFWwindow* w, double x, double y)
{
	Game::instance()->scrolled({ (float)x, (float)y });
}

void JoshoEngine::_keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		Game::instance()->keyDown(key, scancode, mods);
		break;

	case GLFW_RELEASE:
		Game::instance()->keyUp(key, scancode, mods);
		break;

	case GLFW_REPEAT:
		Game::instance()->keyRepeat(key, scancode, mods);
		break;

	default:
		break;
	}
}

void JoshoEngine::_charCallback(GLFWwindow* w, unsigned c)
{
	Game::instance()->charTyped(c);
}

void Game::registerCallbacks()
{
	GLFWwindow* w = glWindow;

	glfwSetErrorCallback(_errorCallback);
	glfwSetWindowPosCallback(w, _windowPositionCallback);
	glfwSetWindowSizeCallback(w, _windowSizeCallback);
	glfwSetWindowCloseCallback(w, _windowCloseCallback);
	glfwSetWindowRefreshCallback(w, _windowRefreshCallback);
	glfwSetWindowFocusCallback(w, _windowFocusCallback);
	glfwSetWindowIconifyCallback(w, _windowIconifyCallback);
	glfwSetFramebufferSizeCallback(w, _framebufferSizeCallback);
	glfwSetMouseButtonCallback(w, _mouseButtonCallback);
	glfwSetCursorPosCallback(w, _cursorPositionCallback);
	glfwSetCursorEnterCallback(w, _cursorEnterCallback);
	glfwSetScrollCallback(w, _mouseScrollCallback);
	glfwSetKeyCallback(w, _keyCallback);
	glfwSetCharCallback(w, _charCallback);
}

void Game::toggleFullscreen()
{
	window->toggleFullscreen();
	glWindow = window->currentWindowContext();
	registerCallbacks();
}
