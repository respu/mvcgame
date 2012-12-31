

#ifndef mvcgame_BaseColorView_hpp
#define mvcgame_BaseColorView_hpp

#include <mvcgame/view/IColorView.hpp>
#include <mvcgame/view/Color.hpp>

namespace mvcgame {

	class BaseColorView : public IColorView
	{
	protected:
		Color _bgColor = Colors::Black;
	public:
		virtual void setBackgroundColor(const Color& color);
		virtual const Color& getBackgroundColor() const;
		virtual Color& getBackgroundColor();
	};

}

#endif