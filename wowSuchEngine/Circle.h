#ifndef JOSHOENGINE_CIRCLE_H_
#define JOSHOENGINE_CIRCLE_H_

#include "JoshoEngine.h"
#include "Vector2.h"
#include "Rectangle.h"
#include "Color.h"

namespace JoshoEngine
{
	struct JOSHO_API Circle
	{
	public:
		Vector2 center;
		
		float radius;

		Circle();

		Circle(Vector2 position, float radius);

		bool intersects(const Rectangle& rectangle) const;

		bool intersects(const Circle& circle) const;

		void draw(bool hollow, Color renderColor) const;

		bool inside(Vector2 point) const;
	};
}

#endif
