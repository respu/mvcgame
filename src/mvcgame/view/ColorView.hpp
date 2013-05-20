

#ifndef mvcgame_ColorView_hpp
#define mvcgame_ColorView_hpp

#include <mvcgame/base/Color.hpp>
#include <mvcgame/view/View.hpp>

namespace mvcgame {

	class ColorView : public View
	{
	protected:
		Color _bgColor;
	public:
		ColorView();
		virtual void setBackgroundColor(const Color& color);
		virtual const Color& getBackgroundColor() const;
		virtual Color& getBackgroundColor();
		virtual void draw();
	};

}

#endif