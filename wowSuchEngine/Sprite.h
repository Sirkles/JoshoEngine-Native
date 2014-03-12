#ifndef JOSHOENGINE_SPRITE_H_
#define JOSHOENGINE_SPRITE_H_

#include "JoshoEngine.h"

#include "Texture2D.h"
#include "Rectangle.h"
#include "Color.h"

namespace JoshoEngine
{
	class JOSHO_API Sprite
	{
	public:
		Sprite(const Texture2D* texture, Rectangle sourceRectangle);

		void draw(const Rectangle& destinationRectangle, float rotation = 0.0f, Color color = Color::White) const;

		float getWidth() const;
		float getHeight() const;
	private:
		const Texture2D* texture;
		Rectangle rectangle;
	};
}

#endif
