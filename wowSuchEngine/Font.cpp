#include "stdafx.h"

#include "Font.h"

#include "OGLFT/OGLFT.h"

#include <string>

#include "Vector2.h"
#include "Color.h"

using namespace JoshoEngine;

Font::Font(const char* file, float pointSize, Type renderType, unsigned int dpi)
{
	switch (renderType)
	{
	case Type::Monochrome:
		this->rasterFont = new OGLFT::Monochrome(file, pointSize, dpi);
		break;
	case Type::Transulcent:
		this->rasterFont = new OGLFT::Translucent(file, pointSize, dpi);
		break;
	//case Type::Outline:
		//this->myFont = new OGLFT::Outline(file, pointSize, dpi);
		//break;
	}
}

Font::~Font()
{
	delete this->rasterFont;
}

void Font::setRotation(float rotation)
{
	this->rasterFont->setStringRotation(rotation);
}

void Font::setColor(Color renderColor)
{
	this->rasterFont->setForegroundColor(renderColor.r, renderColor.g, renderColor.b, renderColor.a);
}

void Font::draw(const char* text, Vector2 position) const
{
	this->rasterFont->draw(position.x, position.y, text);
}
