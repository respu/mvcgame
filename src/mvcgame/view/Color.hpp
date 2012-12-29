
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

		constexpr Color(color_t pr, color_t pg, color_t pb, color_t pa) :
		r(pr), g(pg), b(pb), a(pa)
		{
		}

		constexpr Color(color_t pr, color_t pg, color_t pb) :
		r(pr), g(pg), b(pb)
		{
		}

		constexpr Color(colors_t c) :
		r((c & 0xFF0000) >> 16), g((c & 0x00FF00) >> 8), b(c & 0x0000FF), a((c & 0xFF000000) >> 24)
		{
		}
	};

	class Colors final
	{
	private:
		Colors();
	public:
		static constexpr Color White{255, 255, 255};
		static constexpr Color Black{0, 0, 0};
		static constexpr Color Red{255, 0, 0};
		static constexpr Color Green{0, 255, 0};
		static constexpr Color Blue{0, 0, 255};
	};
}

#endif