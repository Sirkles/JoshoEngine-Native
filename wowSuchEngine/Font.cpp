#include "stdafx.h"

#include "Font.h"

#include <string>

#include "Vector2.h"
#include "Color.h"
#include "Game.h"
#include "MathHelp.h"

using namespace JoshoEngine;

Font::Font(const char* file, unsigned int size, unsigned int numGlyphs)
{
	// Set the class variables.
	this->pointSize = size;
	this->numGlyphs = numGlyphs;

	// Instantiates array of textures. (Default 128)
	this->glyphTextures = new GLuint[numGlyphs];

	// Initialize FreeType library.
	if (FT_Init_FreeType(&(this->library)))
	{
		throw new std::runtime_error("Couldn't initialize FreeType library.");
	}

	// Load the font face into memory.
	if (FT_New_Face(this->library, file, 0, &(this->typeFace)))
	{
		throw new std::runtime_error("Couldn't load typeface. Ensure file exists and is of correct format!");
	}
	
	// Tell FreeType to set the point size.
	FT_Set_Char_Size(this->typeFace, size << 6, size << 6, 96, 96);

	// Tell OpenGL to allocate video memory for the glyph textures.
	this->listBase = glGenLists(numGlyphs);
	glGenTextures(numGlyphs, this->glyphTextures);

	// Fill the array with the newly created bitmaps.
	for (unsigned char i = 0; i < numGlyphs; i++)
	{
		this->makeDisplayList(i);
	}

	// We're done with everything so tell everyone they can go home.
	FT_Done_Face(this->typeFace);
	FT_Done_FreeType(this->library);
}

Font::~Font()
{
	// Delete the dynamic memory allocated to the glyph textures.
	delete this->glyphTextures;
}

void Font::setPointSize(unsigned int size)
{
	// Set the new point size.
	FT_Set_Char_Size(this->typeFace, size << 6, size << 6, 96, 96);
	this->pointSize = size;

	// Recreate the array with newly created bitmaps.
	for (unsigned char i = 0; i < numGlyphs; i++)
	{
		this->makeDisplayList(i);
	}
}

unsigned int Font::getPointSize() const
{
	return this->pointSize;
}

void Font::draw(std::string text, Vector2 position, float rotation, Color renderColor) const
{
	renderColor.apply();

	// lol implement

	Color::White.apply();
}

void Font::makeDisplayList(char c)
{
	// Load the glyph for the character.
	if (FT_Load_Glyph(this->typeFace, FT_Get_Char_Index(this->typeFace, c), FT_LOAD_DEFAULT))
	{
		throw new std::runtime_error("Couldn't find the glyph in the typeface.");
	}

	// Turn it into a FT_Glyph object.
	FT_Glyph myGlyph;
	FT_Get_Glyph(this->typeFace->glyph, &myGlyph);

	// Turn that glyph into a bitmap.
	FT_Glyph_To_Bitmap(&myGlyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)myGlyph;

	// Create a reference to the bitmap glyph to make our life easier.
	FT_Bitmap& glyphBitmap = bitmapGlyph->bitmap;

	// OpenGL likes textures that are powers of 2 (eg 512x512). So we'll have to convert it.
	int width = MathHelp::nextPowerOfTwo(glyphBitmap.width);
	int height = MathHelp::nextPowerOfTwo(glyphBitmap.rows);

	// Allocate memory for the glyph's texture data.
	GLubyte* expandedData = new GLubyte[2 * width * height];

	// Make FreeType's bitmap compatible with OpenGL's bitmap.
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			expandedData[2 * (i + j * width)] = 255;
			expandedData[2 * (i + j * width) + 1] = (i >= glyphBitmap.width || j >= glyphBitmap.rows) ? 0 : glyphBitmap.buffer[i + glyphBitmap.width * j];
		}
	}

	// Set up some OpenGL texture parameters.
	glBindTexture(GL_TEXTURE_2D, this->glyphTextures[c]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Now we create the glyph texture in OpenGL.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expandedData);

	// Throw away unneeded data.
	delete expandedData;

	// Let's create the display list.
	glNewList(this->listBase + c, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, this->glyphTextures[c]);

	// Create a space so the characters won't be smooshed together.
	glTranslatef(bitmapGlyph->left, 0, 0);

	// Move the character down in case we have a character like 'g' or 'y'
	glPushMatrix();
	glTranslatef(0, bitmapGlyph->top - glyphBitmap.rows, 0);

	// Since we had to resize to conform with OpenGL's power-of-two texture rule, we need to take into account the extra padding space.
	float x = (float)glyphBitmap.width / (float)width;
	float y = (float)glyphBitmap.rows / (float)height;

	// Draw the texture-mapped quads.
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex2f(0, glyphBitmap.rows);
	glTexCoord2d(0, y); glVertex2f(0, 0);
	glTexCoord2d(x, y); glVertex2f(glyphBitmap.width, 0);
	glTexCoord2d(x, 0); glVertex2f(glyphBitmap.width, glyphBitmap.rows);
	glEnd();
	glPopMatrix();
	glTranslatef(this->typeFace->glyph->advance.x >> 6, 0, 0);

	// Now we're done with the glyph. Let's tell it we're done.
	FT_Done_Glyph(myGlyph);

	// End the list.
	glEndList();
}
