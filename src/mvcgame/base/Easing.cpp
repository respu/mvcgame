
#include <mvcgame/base/Easing.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Time.hpp>

#include <cmath>
#include <cassert>

namespace mvcgame {

	const easing_t Easing::Pi = 3.1415926535897932384626433832795028841971693993751;

	easing_t Easing::linear(easing_t p, easing_t b, easing_t c)
	{
		return c*p + b;
	}

	easing_t Easing::swing(easing_t p, easing_t b, easing_t c)
	{
		return Easing::linear(0.5 - cosf( p*Pi ) / 2, b, c);
	}

    easing_t Easing::expo(easing_t p, easing_t b, easing_t c)
    {
        return (p==0) ? b : c * pow(2, 10 * (p - 1)) + b;
    }
 
    template<>
    Speed Easing::get(easing_t p, Speed start, Speed diff, Function f)
    {
        assert(start.d == diff.d);
        return Speed(
            f(p, start.x, diff.x),
            f(p, start.y, diff.y),
            start.d
        );
    }

    template<>
    Point Easing::get(easing_t p, Point start, Point diff, Function f)
    {
        return Speed(
            f(p, start.x, diff.x),
            f(p, start.y, diff.y)
        );
    }    
}
