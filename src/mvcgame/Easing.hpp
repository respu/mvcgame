//
//  Easing.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_Easing_hpp
#define mvcgame_Easing_hpp

#include <functional>

namespace mvcgame {

	typedef double easing_t;

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
		Easing(){}

	public:

        static const easing_t Pi;

		typedef std::function<easing_t(easing_t p, easing_t b, easing_t c)> Function;

		static easing_t linear(easing_t p, easing_t b, easing_t c);
		static easing_t swing(easing_t p, easing_t b, easing_t c);
	};
}

#endif