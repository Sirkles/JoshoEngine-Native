#include "stdafx.h"

#include "JoshoEngine.h"
#include "Sprite.h"

#include "Texture2D.h"
#include "Rectangle.h"
#include "Color.h"

using namespace JoshoEngine;

Sprite::Sprite(const Texture2D* texture, JoshoEngine::Rectangle sourceRect)
{
	this->texture = texture;
	this->rectangle = sourceRect;
}

void Sprite::draw(const JoshoEngine::Rectangle& destinationRectangle, float rotation, Color color) const
{
	this->texture->draw(destinationRectangle, this->rectangle, rotation, color);
}

float Sprite::getWidth() const
{
	return this->rectangle.width;
}

float Sprite::getHeight() const
{
	return this->rectangle.height;
}
