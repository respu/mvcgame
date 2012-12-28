
#ifndef mvcgame_Color_hpp
#define mvcgame_Color_hpp

#include <cstdint>

namespace mvcgame {

	typedef uint8_t color_t;
	typedef uint16_t colors_t;

	class Color final
	{
	public:
		color_t r = 0;
		color_t g = 0;
		color_t b = 0;
		color_t a = 255;

		Color(color_t r, color_t g, color_t b, color_t a);
		Color(color_t r, color_t g, color_t b);
		Color(colors_t c);

		static const Color White;
		static const Color Black;		
	};

}

#endif