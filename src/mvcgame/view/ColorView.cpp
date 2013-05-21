#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/platform/IViewBridge.hpp>

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
		View::draw();
		std::vector<Point> vertices = getFrame().getVertices();
		getBridge().drawPolygon(vertices, _bgColor);
	}
}