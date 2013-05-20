#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/RootView.hpp>

namespace mvcgame {

	ColorView::ColorView() : _bgColor(Colors::Black)
	{
	}

	void ColorView::setBackgroundColor(const Color& color)
	{
		_bgColor = color;
	}

	const Color& ColorView::getBackgroundColor() const
	{
		return _bgColor;
	}

	Color& ColorView::getBackgroundColor()
	{
		return _bgColor;
	}

	void ColorView::draw()
	{
		std::vector<Point> vertices = getFrame().getVertices();
		getRoot().drawPolygon(vertices, _bgColor);
	}
}