
#include <mvcgame/base/Color.hpp>

namespace mvcgame {

	Color::Color() : r(0), g(0), b(0), a(255)
	{
	}

	Color::Color(color_t pr, color_t pg, color_t pb, color_t pa) :
	r(pr), g(pg), b(pb), a(pa)
	{
	}

	Color::Color(colors_t c) :
	r((c & 0xFF0000) >> 16), g((c & 0x00FF00) >> 8), b(c & 0x0000FF), a((c & 0xFF000000) >> 24)
	{
	}

    std::ostream& operator<<(std::ostream& os, const Color& c)
    {
        unsigned ur = c.r;
        unsigned ug = c.g;
        unsigned ub = c.b;
        unsigned ua = c.a;
    	os << "Color(r=" << ur << ", g=" << ug << "b=" << ub << ", a=" << ua << ")";
    	return os;
    }

	const Color Colors::White = Color(255, 255, 255);
	const Color Colors::Black = Color(0, 0, 0);
	const Color Colors::Red = Color(255, 0, 0);
	const Color Colors::Green = Color(0, 255, 0);
	const Color Colors::Blue = Color(0, 0, 255);
	const Color Colors::Yellow = Color(255, 255, 0);

};