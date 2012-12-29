
#include <mvcgame/view/Color.hpp>

namespace mvcgame {

	Color::Color(color_t pr, color_t pg, color_t pb, color_t pa) :
	r(pr), g(pg), b(pb), a(pa)
	{
	}

	Color::Color(color_t pr, color_t pg, color_t pb) :
	r(pr), g(pg), b(pb)
	{

	}

	Color::Color(colors_t c) :
	r((c & 0xFF0000) >> 16), g((c & 0x00FF00) >> 8), b(c & 0x0000FF), a((c & 0xFF000000) >> 24)
	{

	}

	const Color Color::White(255, 255, 255);
	const Color Color::Black(0, 0, 0);
	const Color Color::Red(255, 0, 0);
	const Color Color::Green(0, 255, 0);
	const Color Color::Blue(0, 0, 255);
}