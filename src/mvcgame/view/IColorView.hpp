

#ifndef mvcgame_IColorView_hpp
#define mvcgame_IColorView_hpp

#include <string>

namespace mvcgame {

	class Color;

	class IColorView
	{
	public:
		virtual void setBackgroundColor(const Color& color) = 0;
	};

}

#endif