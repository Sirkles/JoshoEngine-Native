#ifndef JOSHOENGINE_FONT_H_
#define JOSHOENGINE_FONT_H_

#include "Vector2.h"
#include "Color.h"

#include "OGLFT/OGLFT.h"

namespace JoshoEngine
{
	class JOSHO_API Font
	{
	public:
		enum Type : unsigned int
		{
			// Aliased (jagged).
			Monochrome = 0,

			// Anti-aliased (non-jagged).
			Transulcent = 1,

			// Outline
			//Outline = 2,
		};

		Font(const char* file, float pointSize, Type renderType, unsigned int dpi = 100);

		~Font();

		void setRotation(float rotation);

		void setColor(Color renderColor);

		void draw(const char* text, Vector2 position) const;
	private:
		// Use the higher object in the hierarchy which is Raster.
		OGLFT::Raster* rasterFont;
	};
}

#endif
