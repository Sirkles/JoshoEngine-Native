#ifndef JOSHOENGINE_TEXTURE2D_H_
#define JOSHOENGINE_TEXTURE2D_H_

#include "JoshoEngine.h"

#include "Rectangle.h"
#include "Color.h"

#include <GLFW/glfw3.h>
#include <gl/GL.h>

namespace JoshoEngine
{
	class JOSHO_API Texture2D
	{
	public:
		// ID of current active GL texture.
		static GLuint active;

		// Dimensions of the texture.
		int width;
		int height;

		// The GL texture id associated with this texture.
		GLuint glTexture;

		// Loads a texture from an image file to a GL texture.
		// Returns an id for the texture;
		static GLuint load(const char* file, int* width, int* height, GLenum filter);

		// Default constructor.
		Texture2D(const char* file, GLenum filter = GL_LINEAR);

		// Destructor
		~Texture2D();

		// Draw
		void draw(const Rectangle& frame, float rotation = 0.0f, const Color renderColor = Color::White) const;

		void draw(const Rectangle& frame, const Rectangle& sprite, float rotation = 0.0f, const Color renderColor = Color::White) const;

		// Is the texture currently active?
		bool isActive() const;
	private:
	};
}

#endif
