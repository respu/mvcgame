
#include <mvcgame/Easing.hpp>

namespace mvcgame {

	const easing_t Easing::Pi = 3.1415926535897932384626433832795028841971693993751;
 
	easing_t Easing::linear(easing_t p, easing_t b, easing_t c)
	{
		return c*p + b;
	}

	easing_t Easing::swing(easing_t p, easing_t b, easing_t c)
	{
		p = 0.5 - cosf( p*Pi ) / 2;
		return linear(p, b, c);
	}
 
}
