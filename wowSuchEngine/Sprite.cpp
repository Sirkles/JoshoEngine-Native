#include "stdafx.h"

#include "JoshoEngine.h"
#include "Sprite.h"

#include "Texture2D.h"
#include "Rectangle.h"
#include "Color.h"
#include "Vector2.h"

using namespace JoshoEngine;

Sprite::Sprite(const Texture2D* texture, JoshoEngine::Rectangle sourceRect)
{
	this->texture = texture;
	this->rectangle = sourceRect;
}

Sprite::Sprite(const Texture2D* texture)
{
	this->texture = texture;
	this->autoSize = true;
}

void Sprite::draw(const JoshoEngine::Rectangle& destinationRectangle, float rotation, Color color) const
{
	if (!this->autoSize)
		this->texture->draw(destinationRectangle, this->rectangle, rotation, color);
	else
		this->texture->draw(destinationRectangle, rotation, color);
}

void Sprite::draw(Vector2 destination, float rotation, Color color) const
{
	this->texture->draw(JoshoEngine::Rectangle(destination.x, destination.y, this->texture->width, this->texture->height), rotation, color);
}

float Sprite::getWidth() const
{
	return this->rectangle.width;
}

float Sprite::getHeight() const
{
	return this->rectangle.height;
}
