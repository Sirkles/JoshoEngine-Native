#include "stdafx.h"

#include "JoshoEngine.h"

#include "Circle.h"
#include "Rectangle.h"
#include "Vector2.h"
#include "Helper.h"
#include "Color.h"
#include "Game.h"

using namespace JoshoEngine;

Circle::Circle()
{
	this->radius = 100;
	this->center = Vector2(100, 100);
}

Circle::Circle(Vector2 position, float radius)
{
	this->center = position;
	this->radius = radius;
}

bool Circle::intersects(const JoshoEngine::Rectangle& rectangle) const
{
	float xClamp = Helper::clamp<float>(this->center.x, rectangle.left(), rectangle.right());
	float yClamp = Helper::clamp<float>(this->center.y, rectangle.top(), rectangle.bottom());
	Vector2 v = Vector2(xClamp, yClamp);

	Vector2 direction = this->center - v;
	float distanceSquared = direction.lengthSquared();

	return ((distanceSquared > 0) && (distanceSquared < radius * radius));
}

bool Circle::intersects(const Circle& circle) const
{
	float diff = ((this->center.x - circle.center.x) * (this->center.x - circle.center.x)) + ((this->center.y - circle.center.y) * (this->center.y - circle.center.y));
	return ((this->radius - circle.radius) * (this->radius - circle.radius) <= diff && diff <= (this->radius + circle.radius) * (this->radius + circle.radius));
}

void Circle::draw(bool hollow, Color renderColor) const
{
	if (!hollow)
	{
		glBegin(GL_TRIANGLE_FAN);

		renderColor.apply();

		glVertex2f(this->center.x, this->center.y);

		for (float angle = 0; angle < 360; angle++)
		{
			glVertex2f(this->center.x + sinf(angle) * this->radius, this->center.y + cosf(angle) * this->radius);
		}

		Color::White.apply();

		glEnd();
	}
	else
	{
		glBegin(GL_LINE_LOOP);

		renderColor.apply();

		for (float angle = 0; angle < 360; angle++)
		{
			glVertex2f(this->center.x + sinf(angle) * this->radius, this->center.y + cosf(angle) * this->radius);
		}

		Color::White.apply();

		glEnd();
	}
}

bool Circle::isInside(Vector2 point) const
{
	return (((point.x - this->center.x) * (point.x - this->center.x)) + ((point.y - this->center.y) * (point.y - this->center.y)) < (this->radius * this->radius));
}
