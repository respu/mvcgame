//
//  Easing.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef hydra_Easing_hpp
#define hydra_Easing_hpp

#include <functional>
#include <math.h>

namespace mvcgraphics {

		/**
		 * Easing designed after jquery easing
		 * http://gsgd.co.uk/sandbox/jquery/easing/
		 * http://www.robertpenner.com/easing/
		 *
		 * First value is the percentage of the easing that is done,
		 * Second value is the start value and third the change in
		 * value at the end of the easing.
		 *
		 * @param p percentage of the easing done
		 * @param b beginning value
		 * @param c change in value at the end of the easing
		 * @returns	value for the given time
		 */

	class Easing
	{
	private:
		Easing()
		{
		}

        static const double Pi = 3.1415926535897932384626433832795028841971693993751;

	public:
		typedef std::function<float(float p, float b, float c)> Function;

		static float linear(float p, float b, float c)
		{
			return c*p + b;
		}

		static float swing(float p, float b, float c)
		{
			p = 0.5 - cosf( p*Pi ) / 2;
			return linear(p, b, c);
		}
	};
}

#endif