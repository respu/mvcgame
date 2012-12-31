

#include <mvcgame/view/BaseColorView.hpp>

namespace mvcgame {

	void BaseColorView::setBackgroundColor(const Color& color)
	{
		_bgColor = color;
	}

	const Color& BaseColorView::getBackgroundColor() const
	{
		return _bgColor;
	}

	Color& BaseColorView::getBackgroundColor()
	{
		return _bgColor;
	}
}