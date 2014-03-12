#include "stdafx.h"

#include <math.h>

#include "JoshoEngine.h"
#include "Helper.h"
#include "Rectangle.h"
#include "Color.h"

using namespace JoshoEngine;

Rectangle::Rectangle(float x, float y, float width, float height)
: x(x), y(y), width(width), height(height)
{
	// wow much constructor very verbose wow
}

Rectangle::Rectangle(const Vector2& topLeft, const Vector2& bottomRight)
{
	this->x = Helper::getMin(topLeft.x, bottomRight.x);
	this->y = Helper::getMin(topLeft.y, bottomRight.y);
	this->width = abs(bottomRight.x - topLeft.x);
	this->height = abs(bottomRight.y - topLeft.y);
}

JoshoEngine::Rectangle& Rectangle::operator=(const Rectangle& other)
{
	this->x = other.x;
	this->y = other.y;
	this->width = other.width;
	this->height = other.height;

	return *this;
}

void Rectangle::setCenter(const Vector2& center)
{
	this->x += center.x - midX();
	this->y += center.y - midY();
}

bool Rectangle::intersects(const Rectangle& other) const
{
	return !(other.x > x + width || other.x + other.width < x || other.y > y + height || other.y + other.height < y);
}

bool Rectangle::isInside(const Vector2& point) const
{
	return (point.x > this->left() && point.x < this->right() && point.y > this->top() && point.y < this->bottom());
}

void Rectangle::draw(bool hollow, Color renderColor) const
{
	if (!hollow)
	{
		glBegin(GL_QUADS);

		renderColor.apply();

		Vector2 topLeftCorner = this->topLeft();
		glVertex2f(topLeftCorner.x, topLeftCorner.y);

		Vector2 topRightCorner = this->topRight();
		glVertex2f(topRightCorner.x, topRightCorner.y);

		Vector2 bottomRightCorner = this->bottomRight();
		glVertex2f(bottomRightCorner.x, bottomRightCorner.y);

		Vector2 bottomLeftCorner = this->bottomLeft();
		glVertex2f(bottomLeftCorner.x, bottomLeftCorner.y);

		Color::White.apply();

		glEnd();
	}
	else
	{
		glBegin(GL_LINE_LOOP);

		renderColor.apply();

		Vector2 topLeftCorner = this->topLeft();
		glVertex2f(topLeftCorner.x, topLeftCorner.y);

		Vector2 topRightCorner = this->topRight();
		glVertex2f(topRightCorner.x, topRightCorner.y);

		Vector2 bottomRightCorner = this->bottomRight();
		glVertex2f(bottomRightCorner.x, bottomRightCorner.y);

		Vector2 bottomLeftCorner = this->bottomLeft();
		glVertex2f(bottomLeftCorner.x, bottomLeftCorner.y);

		Color::White.apply();

		glEnd();
	}
}

float Rectangle::left() const
{
	return this->x;
}

float Rectangle::midX() const
{
	return ((this->x + this->width) / 2.0f);
}

float Rectangle::right() const
{
	return (this->x + this->width);
}

float Rectangle::top() const
{
	return this->y;
}

float Rectangle::midY() const
{
	return ((this->y + this->height) / 2.0f);
}

float Rectangle::bottom() const
{
	return (this->y + this->height);
}

float Rectangle::diagonal() const
{
	return (sqrtf((this->width * this->width) + (this->height * this->height)));
}

Vector2 Rectangle::topLeft() const
{
	return Vector2(this->x, this->y);
}

Vector2 Rectangle::topCenter() const
{
	return Vector2((this->x + this->width) / 2.0f, this->y);
}

Vector2 Rectangle::topRight() const
{
	return Vector2((this->x + this->width), this->y);
}

Vector2 Rectangle::leftCenter() const
{
	return Vector2(this->x, ((this->y + this->height) / 2.0f));
}

Vector2 Rectangle::center() const
{
	return Vector2(((this->x + this->width) / 2.0f), ((this->y + this->height) / 2.0f));
}

Vector2 Rectangle::rightCenter() const
{
	return Vector2((this->x + this->width), ((this->y + this->height) / 2.0f));
}

Vector2 Rectangle::bottomLeft() const
{
	return Vector2(this->x, ((this->y + this->height)));
}

Vector2 Rectangle::bottomCenter() const
{
	return Vector2(((this->x + this->width) / 2.0f), (this->y + this->height));
}

Vector2 Rectangle::bottomRight() const
{
	return Vector2((this->x + this->width), (this->y + this->height));
}
