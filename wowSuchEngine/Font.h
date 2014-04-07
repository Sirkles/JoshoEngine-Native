#ifndef JOSHOENGINE_FONT_H_
#define JOSHOENGINE_FONT_H_

#include "Vector2.h"
#include "Color.h"

#include <ft2build.h>
#include <freetype.h>

namespace JoshoEngine
{
	class JOSHO_API Font
	{
	public:
		Font(const char* file, unsigned int size, unsigned int numGlyphs = 128);

		~Font();

		// Warning: Don't use this in your update or draw methods!
		// This function runs an algorthim that runs in O(N^2) runtime complexity.
		void setPointSize(unsigned int size);

		unsigned int getPointSize() const;

		void draw(std::string text, Vector2 position, float rotation, Color renderColor) const;
	private:
		// This the aforementioned algorthim. It essentially rebuilds the glyph array.
		void makeDisplayList(char c);

		FT_Library library;
		FT_Face typeFace;
		GLuint* glyphTextures;
		unsigned int pointSize;
		unsigned int numGlyphs;
		GLuint listBase;
	};
}

#endif
