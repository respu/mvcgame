
#ifndef mvcgame_Color_hpp
#define mvcgame_Color_hpp

#include <cstdint>
#include <iostream>

namespace mvcgame {

	typedef uint8_t color_t;
	typedef uint16_t colors_t;

	class Color final
	{
	public:
		color_t r;
		color_t g;
		color_t b;
		color_t a;

		Color();
		Color(color_t pr, color_t pg, color_t pb, color_t pa=255);
		Color(colors_t c);
	};

	/**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const Color& c);

	class Colors final
	{
	private:
		Colors();
	public:
		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Transparent;
	};
}

#endif