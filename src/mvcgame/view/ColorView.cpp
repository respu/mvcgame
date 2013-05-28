#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/platform/IRenderBridge.hpp>

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
		Points vertices = getFrame().size.getVertices();
		getBridge().drawPolygon(vertices, _bgColor);
		View::draw();
	}
}