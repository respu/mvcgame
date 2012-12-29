
#include <mvcgame/Easing.hpp>
#include <math.h>

namespace mvcgame {	

	constexpr easing_t Easing::linear(easing_t p, easing_t b, easing_t c)
	{
		return c*p + b;
	}

	constexpr easing_t Easing::swing(easing_t p, easing_t b, easing_t c)
	{
		return Easing::linear(0.5 - cosf( p*Pi ) / 2, b, c);
	}
 
}
