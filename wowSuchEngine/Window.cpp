#include "stdafx.h"

#include "JoshoEngine.h"
#include "Window.h"

using namespace JoshoEngine;

Window::Window(const char* windowTitle, int x, int y, unsigned int width, unsigned int height, bool resizeable)
{
	this->title = windowTitle;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->resizeable = resizeable;

	this->color = Color::Black;

	this->initialized = true;

	this->keepRatio = false;

	this->fullscreenWindow = NULL;

	glfwWindowHint(GLFW_RESIZABLE, this->resizeable);
	this->glWindow = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
	glfwMakeContextCurrent(this->glWindow);
	this->cursorHidden = true;
	hideCursor(this->cursorHidden);

	this->setPosition(x, y);
	this->updateGL();

	glClearColor(this->color.r, this->color.g, this->color.b, this->color.a);
}

Window::~Window()
{
	if (!this->initialized) return;

	glfwDestroyWindow(this->glWindow);
}

void Window::updateSize(unsigned int width, unsigned int height)
{
	if (keepRatio)
	{
		// Make sure we maintain the aspect ratio
		if (this->width != width || this->height != height)
		{
			if (width >= height)
			{
				this->width = width;
				this->height = width / aspectRatio;
			}
			else
			{
				this->width = height * aspectRatio;
				this->height = height;
			}
		}
	}
	else
	{
		// Just update the window dimensions
		this->width = width;
		this->height = height;
		this->aspectRatio = (float)width / (float)height;
	}
}

void Window::centerWindow()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	this->setPosition((mode->width / 2) - (this->getBounds().right() / 2), (mode->height / 2) - (this->getBounds().bottom() / 2));
}

void Window::updateGL()
{
	if (!this->initialized) return;

	// Set the viewport to cover the new window size
	// To ensure we cover the entire window, use framebuffer size
	int fbwidth, fbheight;
	glfwGetFramebufferSize(this->glWindow, &fbwidth, &fbheight);
	glViewport(0, 0, fbwidth, fbheight);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Origin at top left corner of screen
	glOrtho(0.0, (GLdouble)this->width, (GLdouble)this->height, 0.0, -1.0, 1.0);
}

void Window::didMove(int newX, int newY)
{
	this->x = newX;
	this->y = newY;
}

void Window::didResize(int newWidth, int newHeight)
{
	this->setSize(newWidth, newHeight);
}

void Window::setBackgroundColor(const Color& c)
{
	this->color = c;

	if (!this->initialized) return;

	glClearColor(c.r, c.g, c.b, c.a);
}

void Window::clear()
{
	// Don't check for initialization here because this method is
	// a performance critical one, and the window shouldn't be
	// cleared if it isn't initialized already anyways.
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::render()
{
	// Don't check for initialization here either for the same
	// reasons stated above.
	glfwSwapBuffers(this->currentWindowContext());
}

const char* Window::getTitle()
{
	return this->title;
}

void Window::setTitle(const char* title)
{
	this->title = title;

	if (!this->initialized) return;

	glfwSetWindowTitle(currentWindowContext(), this->title);
}

void Window::setPreservesAspectRatio(bool preserve)
{
	this->keepRatio = preserve;
}

bool Window::preservesAspectRatio()
{
	return this->keepRatio;
}

JoshoEngine::Rectangle Window::getBounds() const
{
	return Rectangle(0.0f, 0.0f, this->width, this->height);
}

unsigned int Window::getWidth()
{
	return width;
}

unsigned int Window::getHeight()
{
	return height;
}

void Window::setSize(unsigned int newWidth, unsigned int newHeight)
{
	// Update the width and height according to the aspect ratio
	this->updateSize(newWidth, newHeight);

	// Actually apply the size change
	if (!this->initialized) return;

	glfwSetWindowSize(currentWindowContext(), this->width, this->height);

	this->updateGL();
}

int Window::getX()
{
	return this->x;
}

int Window::getY()
{
	return this->y;
}

void Window::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;

	if (!this->initialized) return;

	glfwSetWindowPos(currentWindowContext(), this->x, this->y);
}

void Window::hideCursor(bool hide)
{
	this->cursorHidden = hide;

	if (!this->initialized) return;

	glfwSetInputMode(this->currentWindowContext(), GLFW_CURSOR, hide ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
}

void Window::toggleFullscreen()
{
	if (!isFullscreen())
		enableFullscreen();
	else
		disableFullscreen();
}

void Window::enableFullscreen()
{
	if (!isFullscreen())
	{
		fullscreenWindow = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), glWindow);
		glfwMakeContextCurrent(fullscreenWindow);
		hideCursor(cursorHidden);
		updateGL();
		glClearColor(color.r, color.g, color.b, color.a);
	}
}

void Window::disableFullscreen()
{
	if (isFullscreen())
	{
		glfwDestroyWindow(fullscreenWindow);
		fullscreenWindow = NULL;
		glfwMakeContextCurrent(glWindow);
		hideCursor(cursorHidden);
		setPosition(x, y);
		updateGL();
	}
}

bool Window::isFullscreen()
{
	return this->fullscreenWindow != NULL;
}

GLFWwindow* Window::currentWindowContext()
{
	if (this->isFullscreen())
		return this->fullscreenWindow;
	return this->glWindow;
}
