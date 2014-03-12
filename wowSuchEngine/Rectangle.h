#ifndef JOSHOENGINE_RECTANGLE_H_
#define JOSHOENGINE_RECTANGLE_H_

#include "JoshoEngine.h"
#include "Vector2.h"
#include "Color.h"

#if WIN32
#pragma message("JoshoEngine: Ensure you are using JoshoEngine::Rectangle as opposed to using plain Rectangle, as there is a naming conflict with WinGDI's Rectangle!")
#endif

namespace JoshoEngine
{
	struct JOSHO_API Rectangle
	{
		// Attributes.
		float x;
		float y;
		float width;
		float height;

		// Creates Rectangle instance with the supplied position and size values.
		Rectangle(float x = 0, float y = 0, float width = 0, float height = 0);

		// Creates Rectangle instance with the supplied vectors for the opposite corners.
		Rectangle(const Vector2& topLeft, const Vector2& bottomRight);

		// Assignment operator.
		Rectangle& operator=(const Rectangle& other);

		// Sets the center of the Rectangle.
		void setCenter(const Vector2& center);

		// Checks if two Rectangles are intersecting.
		bool intersects(const Rectangle& other) const;

		bool isInside(const Vector2& point) const;

		void draw(bool hollow, Color renderColor) const;

		// The x coordinate of the left side.
		float left() const;
		// The x coordinate of the center.
		float midX() const;
		// The x coordinate of the right side.
		float right() const;
		// The y coordinate of the top.
		float top() const;
		// The y coordinate of the center.
		float midY() const;
		// The y coordinate of the bottom.
		float bottom() const;

		// Calculates the length of the rectangle's diagonal.
		float diagonal() const;

		Vector2 topLeft() const;
		Vector2 topCenter() const;
		Vector2 topRight() const;
		Vector2 leftCenter() const;
		Vector2 center() const;
		Vector2 rightCenter() const;
		Vector2 bottomLeft() const;
		Vector2 bottomCenter() const;
		Vector2 bottomRight() const;
	};
}

#endif